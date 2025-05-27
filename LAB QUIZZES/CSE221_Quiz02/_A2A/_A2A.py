import os, sys, time, random, threading, subprocess
from _A2A_Solution import solve
test, best, score, batch, total = 0, 0, 0, 0, 0
timeLimit, nBatch = 1, 10
weight = [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
nTest = [0, 10, 100, 100, 100, 100, 100, 100, 10, 10, 10]
maxN = [ 0, 10, 10, 100, 100, 1000, 1000, 10000, 100000, 1000000, 1000000]
maxS = [0, 1_000, 1_000_000, 1_000_000, 1_000_000_000, 1_000_000, 1_000_000_000, 1_000_000, 1_000_000_000, 1_000_000, 1_000_000_000]
N, S = 0, 0
A = []
res = None
def printCase(verdict, test, N, S, A):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("S = " + str(S) + "\n")
            fout.write("A = " + str(A) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, S, A)
    os._exit(1)
def validIndex(i):
    return i > 0 and i <= N
def checkSoln():
    if(len(res) != 2):
        exitCase("WrongAnswer")
    if(res[0] != -1):
        if(not validIndex(res[0]) or not validIndex(res[1]) or res[0] == res[1]):
            exitCase("WrongAnswer")
        if(A[res[0] - 1] + A[res[1] - 1] != S):
            exitCase("WrongAnswer");
    else:
        i, j = 0, N - 1
        while i < j: 
            if(A[i] + A[j] == S):
                exitCase("WrongAnswer")
            if A[i] + A[j] > S:
                j -= 1
            else:
                i += 1
def processBatch():
    global test, N, S, A, res
    test = 1
    while test <= nTest[batch]:
        N = random.randint(2, maxN[batch])
        A = [None] * N
        D = maxS[batch] // N
        for i in range(N):
            A[i] = (random.randint(1 if i == 0 else A[i - 1], maxS[batch] - (N - i - 1) * D))
        OK = (random.randint(0, 1) == 1)
        if(OK):
            i = random.randint(0, N - 1)
            j = i
            while(i == j):
                j = random.randint(0, N - 1)
            S = A[i] + A[j]
        else:
            S = random.randint(1, maxS[batch])
        res = solve(N, S, A.copy())
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
if os.path.exists("_A2A_" + ID + ".py"):
    with open("_A2A_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A2A.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A2A_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A2A_" + ID + ".py")
    with open("_A2A_" + ID + ".py", "a") as fout:
        with open("_A2A_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
