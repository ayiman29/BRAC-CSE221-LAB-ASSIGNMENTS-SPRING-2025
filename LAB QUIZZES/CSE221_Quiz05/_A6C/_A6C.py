import os, sys, time, random, threading, subprocess
from _A6C_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 4; nBatch = 14; N = 0; X1 = 0; Y1 = 0; X2 = 0; Y2 = 0
weight = [ 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
nTest =  [0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5]
res = 0

def printCase(verdict, test, N, X1, Y1, X2, Y2):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("X1 = " + str(X1) + "\n")
            fout.write("Y1 = " + str(Y1) + "\n")
            fout.write("X2 = " + str(X2) + "\n")
            fout.write("Y2 = " + str(Y2) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, X1, Y1, X2, Y2)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, N, X1, Y1, X2, Y2
    start = time.time()
    res = solve(N, X1, Y1, X2, Y2)
    finish = time.time()
    elapsed += finish - start
    
    with open("_A6C_output.txt", "w") as fout:
        fout.write(str(res))


    ret = subprocess.run('_A6C_Judge.out _A6C_input.txt _A6C_output.txt', shell = True)
    if ret.returncode != 0:
        exitCase("WrongAnswer")

def processBatch():
    global test, N, X1, Y1, X2, Y2
    sys.setrecursionlimit(10**6)
    test = 1
    while test <= nTest[batch]:
        cmd = "_A6C_Gen.out " + str(batch) + " " + str(test) + " > _A6C_input.txt"
        subprocess.run(cmd, shell = True)
        with open('_A6C_input.txt') as temp:
            N = int(temp.readline())
            X1, Y1 = list(map(int, temp.readline().split()))
            X2, Y2 = list(map(int, temp.readline().split()))
            
        
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
if os.path.exists("_A6C_" + ID + ".py"):
    with open("_A6C_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A6C.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A6C_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A6C_" + ID + ".py")
    with open("_A6C_" + ID + ".py", "a") as fout:
        with open("_A6C_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
