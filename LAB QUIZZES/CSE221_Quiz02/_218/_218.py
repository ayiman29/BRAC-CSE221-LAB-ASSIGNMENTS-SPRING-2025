import os, sys, time, random, threading, subprocess
from _218_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 25; N = 0; M = 0
weight = [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
nTest = [0, 2, 10, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 1, 100000, 10000, 1000, 100, 10, 100000, 10000, 1000, 100, 10]
maxNM = [0, 10, 10, 100, 10, 100, 1000, 10, 100, 1000, 10000, 10, 100, 1000, 10000, 100000, 10, 100, 1000, 10000, 100000, 100, 1000, 10000, 100000, 1000000]
list1 = []; list2 = []; res = []
def printCase(verdict, test, list1, list2):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(list1)) + "\n")
            fout.write("M = " + str(len(list2)) + "\n")
            fout.write("list1 = " + str(list1) + "\n")
            fout.write("list2 = " + str(list2) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, list1.copy(), list2.copy())
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, list1, list2, res
    start = time.time()
    res = solve(list1.copy(), list2.copy())
    finish = time.time()
    elapsed += finish - start
    i = len(list1) - 1
    j = len(list2) - 1
    k = 0
    while 0 <= i or 0 <= j:
        if k == len(res) or ((0 <= i and res[k] != list1[i]) and (0 <= j and res[k] != list2[j])):
            exitCase("WrongAnswer")
        while 0 <= i and list1[i] == res[k]:
            i -= 1
        while 0 <= j and list2[j] == res[k]:
            j -= 1
        k += 1
    if k != len(res) or any(res[i] >= res[i - 1] for i in range(1, k)):
        exitCase("WrongAnswer")
def processBatch():
    global test, N, M, list1, list2
    if batch == 1:
        test = 1
        list1 = [1, 2, 2, 3, 4]
        list2 = [2, 2, 3, 3, 5, 6]
        N = len(list1)
        M = len(list2)
        checkSoln()
        test = 2
        list1 = [2, 4, 5, 5, 8, 9, 9, 12, 15]
        list2 = [1, 1, 5, 6, 7, 12, 12, 20]
        N = len(list1)
        M = len(list2)
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        list1 = []
        list2 = []
        N = random.randint(1, maxNM[batch])
        M = random.randint(1, maxNM[batch])
        i = 0
        while i < N:
            if 0 < i and random.randint(0, 1) != 0:
                list1.append(0)
            else:
                list1.append(random.randint(1, 1000000000 // N))
            if 0 < i:
                list1[i] = min(1000000000, list1[i] + list1[i - 1])
            i += 1
        i = 0
        while i < M:
            if 0 < i and random.randint(0, 1) != 0:
                list2.append(0)
            else:
                list2.append(random.randint(1, 1000000000 // M))
            if 0 < i:
                list2[i] = min(1000000000, list2[i] + list2[i - 1])
            i += 1
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
if os.path.exists("_218_" + ID + ".py"):
    with open("_218_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _218.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_218_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_218_" + ID + ".py")
    with open("_218_" + ID + ".py", "a") as fout:
        with open("_218_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)