import os, sys, time, random, threading, subprocess, traceback
from _A7E_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 4; nBatch = 14; N = 0; M = 0; Us = []; Vs = []; Ws = []
weight = [ 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
nTest =  [0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5]
res = -1

def printCase(verdict, test, N, M, Us, Vs, Ws):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("M = " + str(M) + "\n")
            fout.write("Us = " + str(Us) + "\n")
            fout.write("Vs = " + str(Vs) + "\n")
            fout.write("Ws = " + str(Ws) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, M, Us, Vs, Ws)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, N, M, Us, Vs, Ws
    start = time.time()
    res = solve(N, M, Us, Vs, Ws)
    finish = time.time()
    elapsed += finish - start
    with open("_A7E_output.txt", "w") as fout:
        fout.write(str(res) + "\n")

    ret = subprocess.run('_A7E_Judge.out _A7E_input.txt _A7E_output.txt', shell = True)
    if ret.returncode != 0:
        exitCase("WrongAnswer")

class MyThread(threading.Thread):
    def __init__(self, target, *args, **kwargs):
        super().__init__(target=target, args=args, kwargs=kwargs)
        self.exception = None

    def run(self):
        try:
            super().run()
        except Exception as e:
            self.exception = e

    def join(self, *args, **kwargs):
        super().join(*args, **kwargs)
        if self.exception:
            raise self.exception
        
def processBatch():
    global test, N, M, Us, Vs, Ws
    sys.setrecursionlimit(10**6)
    test = 1
    while test <= nTest[batch]:
        cmd = "_A7E_Gen.out " + str(batch) + " " + str(test) + " > _A7E_input.txt"
        subprocess.run(cmd, shell = True)
        with open('_A7E_input.txt') as temp:
            lines = temp.readlines()
            N, M = map(int, lines[0].split())
            Us = [0] * M
            Vs = [0] * M
            Ws = [0] * M
            for i in range(M):
                Us[i], Vs[i], Ws[i] = map(int, lines[i + 1].split())
        
        threading.stack_size(128 * 1024 * 1024)  
        thread = MyThread(target=checkSoln)
        thread.start()
        try:
            thread.join()
        except Exception as e:
            print(traceback.format_exc())
            exitCase("WrongAnswer")
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
if os.path.exists("_A7E_" + ID + ".py"):
    with open("_A7E_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A7E.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A7E_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A7E_" + ID + ".py")
    with open("_A7E_" + ID + ".py", "a") as fout:
        with open("_A7E_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
