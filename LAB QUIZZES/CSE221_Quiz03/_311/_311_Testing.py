import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _311_Testing.py
# from _311_Solution import solve
N = 0
arr = []
res = -1
def solve(arr):
    N = len(arr)
    pairs = -1
    # Place your code here
    
    return pairs


# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(4):
#         fin.readline()
#     list1 = ast.literal_eval(fin.readline()[8:])
#     list2 = ast.literal_eval(fin.readline()[8:])

# stdin
# 5 
# 4 2 1 5 3
N = int(input())
arr = list(map(int, input().split()))


# # hardcoded input
# list1 = [1, 2, 2, 3, 4]
# list2 = [2, 2, 3, 3, 5, 6]

start = time.time()
res = solve(arr.copy())
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
