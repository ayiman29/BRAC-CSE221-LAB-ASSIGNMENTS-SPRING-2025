import os, sys, time, random, threading, subprocess
from _311_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 20; N = 0; nSample = 4
weight = [ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ]
nTest = [ 0, 1, 1, 1, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 100000, 10000, 1000, 100, 10 ]
maxNM = [  0, 10, 10, 50, 100, 10, 500, 1000, 50, 100, 5000, 10000, 10, 500, 1000, 50000, 50, 100, 1000, 50000, 500000 ]
samples = [ [], [4, 2, 1, 5, 3], [1, 4, 3, 10], [9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13], [23, 11, 5, 2] ]
arr = []
res = -1
def printCase(verdict, test, arr):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(arr)) + "\n")
            fout.write("arr = " + str(arr) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, arr.copy())
    os._exit(1)
def count(nums, st, ed):
    if st >= ed:
        return 0
    mid = (st + ed) // 2
    tot = count(nums, st, mid) + count(nums, mid + 1, ed)

    j = mid + 1
    for i in range(st, mid + 1):
        while j <= ed and nums[i] > 2 * nums[j]:
            j += 1
        tot += (j - (mid + 1))

    temp = []
    left, right = st, mid + 1
    while left <= mid and right <= ed:
        if nums[left] <= nums[right]:
            temp.append(nums[left])
            left += 1
        else:
            temp.append(nums[right])
            right += 1
    while left <= mid:
        temp.append(nums[left])
        left += 1
    while right <= ed:
        temp.append(nums[right])
        right += 1

    nums[st:ed+1] = temp
    return tot

def checkSoln():
    global start, finish, elapsed, arr, res
    start = time.time()
    res = solve(arr.copy())
    finish = time.time()
    elapsed += finish - start
    k = count(arr.copy(), 0, len(arr) - 1)
    if k != res:
        exitCase("WrongAnswer")
def processBatch():
    global test, N, M, arr
    if batch <= nSample:
        test = 1
        arr = samples[batch]
        N = len(arr)
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        arr = []
        N = random.randint(1, maxNM[batch])
        i = 0
        for i in range(N):
            arr.append(random.randint(1,500000))
        checkSoln()
        test += 1
def limitTime():
    recall = -1
    while elapsed < timeLimit and recall != elapsed:
        recall = elapsed
        time.sleep(timeLimit << 1)
    exitCase("TimeLimitExceeded")
if len(sys.argv) == 2:
    batch = int(sys.argv[1])
    random.seed(batch)
if 1 <= batch and batch <= nBatch:
    print("Running on Batch " + str(batch), flush=True)
    threading.Thread(target=limitTime, daemon=True).start()
    processBatch()
    print("Accepted on Batch " + str(batch) + " in " + f"{elapsed:.9f}" + "s", flush=True)
    os._exit(0)
ID = ""
with open("EnterIDandLanguage.txt") as fin:
    ID = fin.readline().split()[0]
if os.path.exists("_311_" + ID + ".py"):
    with open("_311_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _311.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_311_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_311_" + ID + ".py")
    with open("_311_" + ID + ".py", "a") as fout:
        with open("_311_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
