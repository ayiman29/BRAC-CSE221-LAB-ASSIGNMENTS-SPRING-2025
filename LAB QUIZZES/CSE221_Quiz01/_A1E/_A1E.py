import os, sys, time, random, threading, subprocess
from _A1E_Solution import solve
test, best, score, batch, total = 0, 0, 0, 0, 0
timeLimit, nBatch, N = 2, 5, 0
weight = [0, 1, 2, 2, 2, 3]
nTest = [0, 1000000, 10000, 100, 500, 50]
maxN = [0, 10, 100, 1000, 10000, 100000]
arr, res = [], []
def printCase(verdict, test, arr):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(arr)) + "\n")
            fout.write("arr = " + str(arr) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
    os._exit(1)
def checkSoln(res):
    if not all(res[i] <= res[i + 1] for i in range(len(res) - 1)):
        printCase("WrongAnswer", test, arr.copy())
def limitTime():
    time.sleep(timeLimit)
    printCase("TimeLimitExceeded", test, arr.copy())
if len(sys.argv) == 2:
    batch = int(sys.argv[1])
    random.seed(batch)
if len(sys.argv) != 2 or batch < 1 or nBatch < batch:
    ID = ""
    with open("EnterIDandLanguage.txt") as fin:
        ID = fin.readline().split()[0]
    if os.path.exists("_A1E_" + ID + ".py"):
        with open("_A1E_" + ID + ".py") as fin:
            best = int(fin.readline().split()[2])
    with open("WrongAnswer.txt", "w") as fout:
        pass
    with open("TimeLimitExceeded.txt", "w") as fout:
        pass
    batch = 1
    while batch <= nBatch:
        process = subprocess.run("pypy _A1E.py " + str(batch), capture_output=True, text=True)
        if process.stdout:
            print(process.stdout, end="")
        if process.stderr:
            print(process.stderr, end="")
        if process.returncode == 0:
            score += weight[batch]
        total += weight[batch]
        batch += 1
    if best <= score:
        with open("_A1E_" + ID + ".py", "w") as fout:
            fout.write("# " + ID + " " + str(score) + "\n")
        subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A1E_" + ID + ".py")
        with open("_A1E_" + ID + ".py", "a") as fout:
            with open("_A1E_Solution.py") as code:
                fout.write(code.read())
    print("Tentative score = " + str(score / total) + "/1", flush=True)
    os._exit(0)
print("Running on Batch " + str(batch), flush=True)
start = time.time()
threading.Thread(target=limitTime, daemon=True).start()
if 1 <= batch and batch <= nBatch:
    test = 1
    while test <= nTest[batch]:
        res = []
        arr = []
        N = random.randint(1, maxN[batch])
        i = 1
        while i <= N:
            arr.append(random.randint(1, 1000000000))
            i += 1
        if 1000 < N:
            arr.sort()
        res = solve(arr.copy())
        checkSoln(res)
        test += 1
finish = time.time()
elapsed = finish - start
print("Passed Batch " + str(batch) + " in " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)