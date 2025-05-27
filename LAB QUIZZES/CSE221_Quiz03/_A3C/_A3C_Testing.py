import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _A3C_Testing.py
N = 0; A = 0; res = 0
def solve(A, N):
    res = 0
    MOD = 1000003
    # Place your code here
    return res

# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(2):
#         fin.readline()
#     A = int(fin.readline()[4:])
#     N = int(fin.readline()[4:])

# stdin
# 100
# 7
A = int(input())
N = int(input())

# # hardcoded input
# A = 100
# N = 7

start = time.time()
res = solve(A, N)
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
