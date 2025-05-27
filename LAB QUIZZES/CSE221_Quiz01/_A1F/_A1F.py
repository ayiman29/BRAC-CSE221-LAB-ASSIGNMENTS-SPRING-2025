import os, sys, time, random, threading, subprocess
from _A1F_Solution import solve
test, best, score, batch, total = 0, 0, 0, 0, 0
timeLimit, nBatch, N = 1, 10, 0
weight = [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
nTest = [0, 10, 1000, 100000, 10, 100, 1000, 10000, 1, 10, 100]
maxN = [0, 10, 10, 10, 100, 100, 100, 100, 1000, 1000, 1000]
sIDs, sMarks = [], []
res = None
def printCase(verdict, test, sIDs, sMarks):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(sIDs)) + "\n")
            fout.write("sIDs = " + str(sIDs) + "\n")
            fout.write("sMarks = " + str(sMarks) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, sIDs.copy(), sMarks.copy())
    os._exit(1)
def checkSoln():
    cnt = 0
    arr = []
    arr = [(-sMarks[i], sIDs[i]) for i in range(N)]
    i = 0
    while i < N:
        j = i
        k = i
        while k < N:
            if arr[j] > arr[k]:
                j = k
            k += 1
        if i != j:
            arr[i], arr[j] = arr[j], arr[i]
            cnt += 1
        i += 1
    arr = [(arr[i][1], -arr[i][0]) for i in range(N)]
    if cnt != res[0] or arr != res[1]:
        exitCase("WrongAnswer")
def processBatch():
    global test, N, sIDs, sMarks, res
    test = 1
    while test <= nTest[batch]:
        sIDs = []
        sMarks = []
        N = random.randint(1, maxN[batch])
        i = 1
        while i <= N:
            sIDs.append(i + 1000 - N)
            sMarks.append(random.randint(1, 1000))
            i += 1
        random.shuffle(sIDs)
        res = solve(sIDs.copy(), sMarks.copy())
        checkSoln()
        test += 1
def limitTime():
    time.sleep(timeLimit)
    exitCase("TimeLimitExceeded")
if len(sys.argv) == 2:
    batch = int(sys.argv[1])
    random.seed(batch)
if 1 <= batch and batch <= nBatch:
    print("Running on Batch " + str(batch), flush=True)
    start = time.time()
    threading.Thread(target=limitTime, daemon=True).start()
    processBatch()
    finish = time.time()
    elapsed = finish - start
    print("Passed Batch " + str(batch) + " in " + f"{elapsed:.9f}" + "s", flush=True)
    os._exit(0)
ID = ""
with open("EnterIDandLanguage.txt") as fin:
    ID = fin.readline().split()[0]
if os.path.exists("_A1F_" + ID + ".py"):
    with open("_A1F_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A1F.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A1F_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A1F_" + ID + ".py")
    with open("_A1F_" + ID + ".py", "a") as fout:
        with open("_A1F_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)