import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _218_Testing.py
# from _218_Solution import solve
N = 0; M = 0
list1 = []; list2 = []; res = []
def solve(list1, list2):
    N = len(list1)
    M = len(list2)
    k = N + M
    res = [None]*k
    idx = k - 1

    i = 0
    j = 0
    while i < N and j < M:
        if list1[i] <= list2[j]:
            res[idx] = list1[i]
            idx -= 1
            i += 1

        else:
            res[idx] = list2[j]
            idx -= 1
            j += 1
        if idx + 2 < k:

            if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1

    

    while i < N:
        res[idx] = list1[i]
        i += 1
        idx -= 1
        if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1
    while j < M:
        res[idx] = list2[j]
        j += 1
        idx -= 1
        if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1
    res = res[idx+1::]

    
    
    return res
    
    
    return res
    return res

# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(4):
#         fin.readline()
#     list1 = ast.literal_eval(fin.readline()[8:])
#     list2 = ast.literal_eval(fin.readline()[8:])

# stdin
# 5 6
# 1 2 2 3 4
# 2 2 3 3 5 6
N, M = map(int, "5 6".split())
list1 = list(map(int, "1 2 2 3 4".split()))
list2 = list(map(int, "2 2 3 3 5 6".split()))

# # hardcoded input
# list1 = [1, 2, 2, 3, 4]
# list2 = [2, 2, 3, 3, 5, 6]

start = time.time()
res = solve(list1.copy(), list2.copy())
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)