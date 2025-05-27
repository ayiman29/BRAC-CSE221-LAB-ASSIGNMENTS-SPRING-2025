import os, sys, time, random, threading, subprocess
from _412_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 10; N = 0; nSample = 2
weight = [ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ]
nTest = [ 0, 1, 1, 100, 10,  1000, 10, 1,   100,    1000, 100 ]
maxNM = [  0, 10, 100, 10, 500,  50,  5000, 10000,   1000,   1000, 5000  ]
samples = [ [], [4, 2, 1, 5, 3], [1, 4, 3, 10], [9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13], [23, 11, 5, 2] ]
n = None
sampleArr = [ 
    [],
    [(7,7)],
    [(1,1), (1,2)]
]
sampleN = [0, 10, 2]
sampleAns = [0, 7, 1]
sampleInitX = [0, 6, 2]
sampleInitY = [0, 7, 2]
arr = []
res = None
initX = -1; initY = -1
N = 0; M = 0
def printCase(verdict, test, N, initX, initY, arr):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("M = " + str(len(arr)) + "\n")
            fout.write("initX = " + str(initX) + "\n")
            fout.write("initY = " + str(initY) + "\n")
            fout.write("arr = " + str(arr) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, initX, initY, arr.copy())
    os._exit(1)

def checkSoln(val):
    global start, finish, elapsed, list1, list2, res
    start = time.time()
    res = solve(N, initX, initY, arr.copy())
    finish = time.time()
    elapsed += finish - start
    if val != res:
        exitCase("WrongAnswer")
def processBatch():
    global test, N, M, initX, initY, arr
    
    if batch <= nSample:
        test = 1
        arr = sampleArr[batch]
        initX = sampleInitX[batch]
        initY = sampleInitY[batch]
        N = sampleN[batch]
        checkSoln(sampleAns[batch])
        return
    
    test = 1
    while test <= nTest[batch]:
        tot = 0
        arr = set()
        block = []
        N = random.randint(2, maxNM[batch])
        M = random.randint(1, min(100, N * N - 1))
        initX = random.randint(1, N)
        initY = random.randint(1, N)
        while len(arr) < M:
            x = random.randint(1, N)
            y = random.randint(1, N)
            if x == initX and y == initY:
                continue
            arr.add((x, y))
            if abs(x - initX) < 2 and abs(y - initY) < 2:
                dx = x - initX
                dy = y - initY
                if (dx, dy) not in block:
                    tot+=1
                    block.append((dx, dy))
        arr = list(arr)
        ans = 8
        if (initX == 1 or initX == N) and (initY == 1 or initY == N):
            ans -= 5
        elif initX == 1 or initX == N:
            ans -= 3
        elif initY == 1 or initY == N:
            ans -= 3
        checkSoln(ans - tot)
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
if os.path.exists("_412_" + ID + ".py"):
    with open("_412_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _412.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_412_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_412_" + ID + ".py")
    with open("_412_" + ID + ".py", "a") as fout:
        with open("_412_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
