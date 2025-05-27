import os, sys, time, random, threading, subprocess
from _312_Solution import solve
start = 0; finish = 0; elapsed = 0
test = 0; best = 0; score = 0; batch = 0; total = 0
timeLimit = 1; sBatch = 2; nBatch = 10; N = 0
weight = [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
nTest = [0, 1, 1, 1, 1, 100, 10000, 1, 100, 10000, 1000000]
maxNM = [0, 5, 10, 100, 1000, 100, 10, 10000, 1000, 100, 10]
preOrderSample = [[], [3, 9, 20, 15, 7], [1, 2, 3, 4, 5, 6, 7, 8, 9, 500000]]
postOrderSample = [[], [9, 15, 7, 20, 3], [500000, 9, 8, 7, 6, 5, 4, 3, 2, 1]]
preOrder = []; postOrder = []; result = []; newOrder = []
def printCase(verdict, test, preOrder, postOrder):
    if os.path.getsize(verdict + ".txt") == 0:
        with open(verdict + ".txt", "w") as fout:
            fout.write("batch = " + str(batch) + "\ntest = " + str(test) + "\n")
            fout.write("N = " + str(len(preOrder)) + "\n")
            fout.write("preOrder = " + str(preOrder) + "\n")
            fout.write("postOrder = " + str(postOrder) + "\n")
    print(verdict + " on Batch " + str(batch), flush=True)
def exitCase(verdict):
    printCase(verdict, test, preOrder.copy(), postOrder.copy())
    os._exit(1)
def build2(preLeft, resLeft, span):
    global newOrder
    if span < 1:
        return
    i = 0
    while True:
        if preOrder[preLeft] == result[resLeft + i]:
            build2(preLeft + 1, resLeft, i)
            build2(preLeft + 1 + i, resLeft + i + 1, span - 1 - i)
            break
        i += 1
    newOrder.append(preOrder[preLeft])
def checkSoln():
    global start, finish, elapsed, preOrder, postOrder, result, newOrder
    start = time.time()
    result = solve(preOrder.copy(), postOrder.copy())
    finish = time.time()
    elapsed += finish - start
    if timeLimit < elapsed:
        exitCase("TimeLimitExceeded")
    if len(result) != N:
        exitCase("WrongAnswer")
    newOrder = []
    build2(0, 0, N)
    if postOrder != newOrder:
        exitCase("WrongAnswer")
def build(left, right):
    global postOrder
    if right < left:
        return
    if left < right:
        mid = random.randint(left + 1, right)
        build(left + 1, mid)
        build(mid + 1, right)
    postOrder.append(preOrder[left])
def processBatch():
    global test, N, preOrder, postOrder, result, newOrder
    if batch <= sBatch:
        test = 1
        preOrder = preOrderSample[batch]
        postOrder = postOrderSample[batch]
        N = len(preOrder)
        checkSoln()
        return
    test = 1
    while test <= nTest[batch]:
        preOrder = []
        postOrder = []
        N = random.randint(1, maxNM[batch])
        hashTable = set()
        i = 0
        while i < N:
            j = random.randint(1, 500000)
            while j in hashTable:
                j = random.randint(1, 500000)
            hashTable.add(j)
            preOrder.append(j)
            i += 1
        build(0, N - 1)
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
if os.path.exists("_312_" + ID + ".py"):
    with open("_312_" + ID + ".py") as fin:
        best = int(fin.readline().split()[2])
open("WrongAnswer.txt", "w").close()
open("TimeLimitExceeded.txt", "w").close()
batch = 1
while batch <= nBatch:
    process = subprocess.run("pypy _312.py " + str(batch), capture_output=True, text=True)
    if process.stdout:
        print(process.stdout, end="")
    if process.stderr:
        print(process.stderr, end="")
    if process.returncode == 0:
        score += weight[batch]
    total += weight[batch]
    batch += 1
if best <= score:
    with open("_312_" + ID + ".py", "w") as fout:
        fout.write("# " + ID + " " + str(score) + "\n")
    subprocess.run("cmd /c echo # %COMPUTERNAME% %USERNAME%>>_312_" + ID + ".py")
    with open("_312_" + ID + ".py", "a") as fout:
        with open("_312_Solution.py") as code:
            fout.write(code.read())
print("Tentative score = " + str(score / total) + "/1", flush=True)
os._exit(0)