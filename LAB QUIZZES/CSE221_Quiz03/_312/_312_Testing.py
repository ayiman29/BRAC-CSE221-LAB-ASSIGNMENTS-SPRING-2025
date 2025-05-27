import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _312_Testing.py
# from _312_Solution import solve
N = 0
preOrder = []; postOrder = []; result = []
def solve(preOrder, postOrder):
    N = len(preOrder)
    result = []
    # Place your code here
    return result

# # file input
# # with open("TimeLimitExceeded.txt") as fin:
# # with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     for i in range(4):
#         fin.readline()
#     preOrder = ast.literal_eval(fin.readline()[11:])
#     postOrder = ast.literal_eval(fin.readline()[12:])

# stdin
# 5
# 3 9 20 15 7
# 9 15 7 20 3
N = int(input())
preOrder = list(map(int, input().split()))
postOrder = list(map(int, input().split()))

# # hardcoded input
# preOrder = [3, 9, 20, 15, 7]
# postOrder = [9, 15, 7, 20, 3]

start = time.time()
result = solve(preOrder.copy(), postOrder.copy())
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(result))

# stdout
print(result)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
