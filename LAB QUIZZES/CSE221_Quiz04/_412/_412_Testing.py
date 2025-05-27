import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _412_Testing.py
# from _412_Solution import solve
N = 0
M = 0
initX = -1
initY = -1
arr = []
res = -1

def solve(n, initX, initY, arr):
    m = len(arr)
    ans = 0
    for i in range(initX-1, initX+2):
        for j in range(initY-1, initY+2):
            if (i, j) not in arr and i > 0 and i < n+1 and j >0 and j < n+1 and (i, j) != (initX, initY):
                ans += 1
                print(i, j, "WORKS")
            else:
                print(i, j)

    return ans


# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(4):
#         fin.readline()
#     list1 = ast.literal_eval(fin.readline()[8:])
#     list2 = ast.literal_eval(fin.readline()[8:])

# stdin
# 4 3
# 1 3
# 2 3
# 1 1
# 3 4 

'''
N, M = map(int, input().split())
initX, initY = map(int, input().split())

for i in range(M):
    x, y = map(int, input().split())
    arr.append((x,y))
'''

# # hardcoded input
# list1 = [1, 2, 2, 3, 4]
# list2 = [2, 2, 3, 3, 5, 6]
N = 7
M = 1
initX = 6
initY = 7
arr = [(7,7)]

start = time.time()
res = solve(N, initX, initY, arr.copy())
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
