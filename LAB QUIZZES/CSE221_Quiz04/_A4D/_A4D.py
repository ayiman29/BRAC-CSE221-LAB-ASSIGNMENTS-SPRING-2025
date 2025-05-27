import os, sys, time, random, threading, subprocess
from _A4D_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 13; N = 0; 
weight = [ 0, 6, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8]
nTest =  [0, 1, 1, 1, 10000, 10000, 1000, 1000, 100, 100, 50, 50, 20, 20]
maxN =  [ 0, 5, 5, 8, 10,  10, 100, 100, 1000, 1000, 10000, 10000, 100000, 100000]
res = False
perm = []
edges = []
o = 0

def printCase(verdict, test, N, edges):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(N) + "\n")
            fout.write("edges = " + str(edges) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, N, edges)
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, N, edges, o
    start = time.time()
    res = solve(N, edges)
    finish = time.time()
    elapsed += finish - start
    o = (o == 0 or o == 2)
    if o != res:
        exitCase("WrongAnswer")
def processBatch():
    global test, N, edges, o, perm
   
    if batch == 1:
        N = 5
        edges = [(0, 1), (0, 2), (0, 3), (0, 4), (1, 2), (1, 3), (2, 3), (2, 4), (3, 4)]
        o = 0
        checkSoln()
        return
    elif batch == 2:
        N = 5
        edges = [(0, 1), (0, 2), (0, 3), (2, 3), (2, 4), (3, 4)]
        o = 1
        checkSoln()
        return
    elif batch == 3:
        N = 8
        edges = [(0, 2), (0, 4), (1, 0), (1, 4), (1, 6), (1, 5), (2, 4), (2, 5), (3, 2), (4, 3), (4, 7), (5, 3), (6, 4), (6, 2), (6, 5), (7, 0)]
        o = 0
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        N = random.randint(1, maxN[batch])
        M = random.randint(N - 1, 2 * maxN[batch])
        perm = [0] * N
        par = [0] * N
        edges = []
        o = 0
        for i in range(N):
            perm[i] = i
        random.shuffle(perm)
        for i in range(1, N):
            u = perm[random.randint(0, i - 1)]
            v = perm[i]
            par[u]^=1
            par[v]^=1
            if(par[u] == par[v]):
                o += 4 * par[u] - 2
            edges.append((u, v))
            M -= 1
        A = random.randint(0, 2)
        if(N <= 3 or A == 2):
            while(M > N / 2):
                u = random.randint(0, N - 1)
                v = random.randint(0, N - 1)
                par[u]^=1
                par[v]^=1
                if(u != v and par[u] == par[v]):
                    o += 4 * par[u] - 2
                edges.append((u, v))
                M -= 1
            oo = []
            for i in range(N):
                if(par[i] == 1):
                    oo.append(i)
            random.shuffle(oo)
            for i in range(0, len(oo), 2):
                u = oo[i]
                v = oo[i + 1]
                par[u]^=1
                par[v]^=1
                if(u != v and par[u] == par[v]):
                    o += 4 * par[u] - 2
                edges.append((u, v))
                M -= 1
        else:
            while(M > A):
                u = random.randint(0, N - 1)
                v = random.randint(0, N - 1)
                par[u]^=1
                par[v]^=1
                if(u != v and par[u] == par[v]):
                    o += 4 * par[u] - 2
                edges.append((u, v))
                M -= 1
            if(A == 1 and o <= 2):
                ee = []
                for i in range(N):
                    if(par[i] == 0):
                        ee.append(i)
                u = ee[0]
                v = ee[1]
                par[u]^=1
                par[v]^=1
                if(u != v and par[u] == par[v]):
                    o += 4 * par[u] - 2
                edges.append((u, v))
                M -= 1
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
if os.path.exists("_A4D_" + ID + ".py"):
    with open("_A4D_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A4D.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A4D_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A4D_" + ID + ".py")
    with open("_A4D_" + ID + ".py", "a") as fout:
        with open("_A4D_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
