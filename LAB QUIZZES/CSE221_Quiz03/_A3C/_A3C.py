import os, sys, time, random, threading, subprocess
from _A3C_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 14; N = 0; A = 0; ten_9 = 1000000000; MOD=1000003
weight = [0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
nTest =  [0, 1, 1, 1, 1, 1000, 1000, 10000, 1000, 10000, 10, 1000, 1000, 10000, 10000]
maxN =  [ 0, 0, 0, 0, 0,  10,  100, 100, 1000, 1000, 1000000, 1000000, ten_9, ten_9 * 1000, ten_9 * ten_9]
res = 0
def printCase(verdict, test, A, N):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("A = " + str(A) + "\n")
            fout.write("N = " + str(N) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, A, N)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, A, N, res
    start = time.time()
    res = solve(A, N)
    finish = time.time()
    elapsed += finish - start
    if timeLimit < elapsed:
        exitCase("TimeLimitExceeded")
    if(res < 0 or res >= MOD):
        exitCase("WrongAnswer")
    ans=1
    tempN=N
    while(N):ans=ans*A%MOD if (N&1) == 1 else ans;N>>=1;A=A*A%MOD
    N=tempN
    if(res != ans):
        exitCase("WrongAnswer")

def processBatch():
    global test, N, A
    if (batch == 1):
        test = 1
        A = 100
        N = 3
        checkSoln()
        return
    if (batch == 2):
        test = 1
        A = 100
        N = 7
        checkSoln()
        return
    if (batch == 3):
        test = 1
        A = 1000000
        N = ten_9 * ten_9
        checkSoln()
        return
    if (batch == 4):
        test = 1
        A = 1
        N = ten_9
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        A = random.randint(1, 1000000)
        N = random.randint(1, maxN[batch])
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
if os.path.exists("_A3C_" + ID + ".py"):
    with open("_A3C_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A3C.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A3C_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A3C_" + ID + ".py")
    with open("_A3C_" + ID + ".py", "a") as fout:
        with open("_A3C_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
