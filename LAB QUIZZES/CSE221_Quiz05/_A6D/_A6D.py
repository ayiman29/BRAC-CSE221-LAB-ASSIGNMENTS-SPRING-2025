import os, sys, time, random, threading, subprocess
from _A6D_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 4; nBatch = 14; N = 0; R = 0; edges = []
weight = [ 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
nTest =  [0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5]
res = []

def printCase(verdict, test, N, R, edges):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("R = " + str(R) + "\n")
            fout.write("edges = " + str(edges) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, R, edges)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, N, R, edges
    start = time.time()
    res = solve(N, R, edges)
    finish = time.time()
    elapsed += finish - start
    if len(res) != N + 1:
        exitCase("WrongAnswer")
    with open("_A6D_output.txt", "w") as fout:
        res[0] = 0
        for i in range(0, N + 1):
            fout.write(str(res[i]) + " ")
        fout.write("\n")


    ret = subprocess.run('_A6D_Judge.out _A6D_input.txt _A6D_output.txt', shell = True)
    if ret.returncode != 0:
        exitCase("WrongAnswer")

def processBatch():
    global test, N, R, edges
    sys.setrecursionlimit(10**6)
    test = 1
    while test <= nTest[batch]:
        cmd = "_A6D_Gen.out " + str(batch) + " " + str(test) + " > _A6D_input.txt"
        subprocess.run(cmd, shell = True)
        with open('_A6D_input.txt') as temp:
            N, R = list(map(int, temp.readline().split()))
            edges = []
            for _ in range(N-1):
                u, v = list(map(int, temp.readline().split()))
                edges.append((u, v))
        
        threading.stack_size(128 * 1024 * 1024)     
        thread = threading.Thread(target=checkSoln, daemon=True)
        thread.start()
        thread.join()
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
if os.path.exists("_A6D_" + ID + ".py"):
    with open("_A6D_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A6D.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A6D_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A6D_" + ID + ".py")
    with open("_A6D_" + ID + ".py", "a") as fout:
        with open("_A6D_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
