import os, sys, time, random, threading, subprocess
from _A3A_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; nBatch = 14; N = 0
weight = [0, 5, 5, 5, 5,   8,   8,   8,   8,    8,    8,    8,     8,     8,       8]
nTest =  [0, 1, 1, 1, 1, 100, 100,  10, 100,   10,  100,  100,    10,    10,      10]
maxN =  [ 0, 5, 5, 5, 7,  10,  20, 100, 100, 1000, 1000, 1000, 10000, 100000, 100000]
A = []; res = 0
def printCase(verdict, test, A):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(A)) + "\n")
            fout.write("A = " + str(A) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, A.copy())
    os._exit(1)
def checkSoln():
    global start, finish, elapsed, list1, list2, res
    start = time.time()
    res = solve(A.copy())
    finish = time.time()
    elapsed += finish - start
    st = []
    st.append((0, len(A) - 1))
    temp = [0] * len(A)
    while(len(st) > 0):
        a, b = st.pop()
        if(a == b):
            continue
        if(b < 0):
            b = -b
            m = (a + b) >> 1
            i = a ; j = m + 1
            while(i <= m or j <= b):
                if(i > m or j <= b and A[j] < A[i]):
                    temp[i + j - a - m - 1] = A[j]
                    j += 1
                else:
                    res -= j - m - 1
                    temp[i + j - a - m - 1] = A[i]
                    i += 1
            for i in range(a, b + 1):
                A[i] = temp[i - a]
        else:
            m = (a + b) >> 1
            st.append((a, -b))
            st.append((a, m))
            st.append((m + 1, b))
    
    if(res != 0):
        exitCase("WrongAnswer")

def processBatch():
    global test, N, A
    if batch == 1:
        test = 1
        A = [1, 2, 5, 4, 3]
        N = len(A)
        checkSoln()
        return
    if batch == 2:
        test = 1
        A = [1, 2, 3, 4, 5]
        N = len(A)
        checkSoln()
        return
    if batch == 3:
        test = 1
        A = [5, 4, 3, 2, 1]
        N = len(A)
        checkSoln()
        return
    if batch == 4:
        test = 1
        A = [6, 4, 2, 5, 7, 3, 1]
        N = len(A)
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        N = random.randint(1, maxN[batch])
        A = [0] * N
        temp = [0] * (N + 1)
        for i in range(N):
            A[i] = random.randint(1, N)
            temp[A[i]] += 1
        for i in range(1, N + 1):
            temp[i] += temp[i - 1]
        for i in range(N):
            A[i] = temp[A[i]]
            temp[A[i]] -= 1
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
if os.path.exists("_A3A_" + ID + ".py"):
    with open("_A3A_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _A3A.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_A3A_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_A3A_" + ID + ".py")
    with open("_A3A_" + ID + ".py", "a") as fout:
        with open("_A3A_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)
