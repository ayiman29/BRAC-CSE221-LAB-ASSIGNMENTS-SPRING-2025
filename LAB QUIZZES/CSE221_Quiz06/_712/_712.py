import os, sys, time, random, threading, subprocess
from _712_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 10; N = 0; M = 0; S = 0; D = 0; K = 0; arr = []
adj = [[]]
u = []
v = []
w = []
weight = [ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
nTest =  [0, 1, 50, 100, 100, 50, 20, 50, 50, 20, 50]
res = -1
edges = []
def printCase(verdict, test, N, M, S, D, K, edges):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("M = " + str(M) + "\n")
            fout.write("S = " + str(S) + "\n")
            fout.write("D = " + str(D) + "\n")
            fout.write("K = " + str(K) + "\n")
            fout.write("edges = " + str(edges) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, M, S, D, K, edges)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, N, M, S, D, K, arr, edges, res
    start = time.time()
    res = solve(N, M, S, D, K, edges)
    finish = time.time()
    elapsed += finish - start
    
    with open("_712_output.txt", "w") as fout:
        fout.write(str(res))
        
    ret = subprocess.run('_712_Judge.out _712_input.txt _712_output.txt', shell = True)
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
    global test, N, M, S, D, K, edges, u, v, w, arr
    # sys.setrecursionlimit(10**6)
    test = 1
    while test <= nTest[batch]:
        cmd = "_712_Gen.out " + str(batch) + " " + str(test) + " > _712_input.txt"
        subprocess.run(cmd, shell = True)
        with open('_712_input.txt') as temp:
            line1 = temp.readline().split()
            N = int(line1[0])
            M = int(line1[1])
            S = int(line1[2])
            D = int(line1[3])
            K = int(line1[4])
            u = list(map(int, temp.readline().split()))
            v = list(map(int, temp.readline().split()))
            w = list(map(int, temp.readline().split()))
            edges = []
            for i in range(M):
                edges.append((u[i], v[i], w[i]))

        threading.stack_size(128 * 1024 * 1024)  
        thread = MyThread(target=checkSoln)
        thread.start()
        try:
            thread.join()
        except Exception as e:
            print(e)
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
if os.path.exists("_712_" + ID + ".py"):
    with open("_712_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _712.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_712_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_712_" + ID + ".py")
    with open("_712_" + ID + ".py", "a") as fout:
        with open("_712_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
