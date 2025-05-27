import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _A3A_Testing.py
N = 0; res = 0
A = []
def solve(A):
    N = len(A)
    res = 0
    # Place your code here
    return res

# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(3):
#         fin.readline()
#     A = ast.literal_eval(fin.readline()[4:])

# stdin
# 5
# 1 2 5 4 3
N = int(input())
A = list(map(int, input().split()))

# # hardcoded input
# N = 5
# A = [1, 2, 5, 4, 3]

start = time.time()
res = solve(A.copy())
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
