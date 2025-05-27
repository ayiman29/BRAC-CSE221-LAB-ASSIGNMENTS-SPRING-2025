import os, sys, time, random, threading, subprocess
N = 0
S = 0
A = []
# Compile and run: pypy _A2A_Testing.py
def solve(N, S, A):
    flag = False
    i, j = 0, len(A) - 1
    while i <= j:
        sum = A[i] + A[j]
        if sum == S:
            flag = True
            break
        if sum > S:
            j -= 1
        else:
            i += 1
    if flag == False:
        return (-1, -1)
    return (i + 1, j + 1)


# stdin
# 4 10
# 1 3 5 7
N, S = list(map(int, "9 27".split()))
A = [35, 219, 321, 350, 501, 527, 757, 838, 845]


# # hardcoded input
# N, S = 4, 10
# A = [1, 3, 5, 7]

start = time.time()
res = solve(N, S, A.copy())
finish = time.time()
elapsed = finish - start

# # stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
# # file input
# with open("TimeLimitExceeded.txt") as fin:
# with open("CustomTest.txt") as fin:
# with open("WrongAnswer.txt") as fin:
#     lines = fin.readlines()
#     N = int(lines[2].split(" ")[2])
#     S = int(lines[3].split(" ")[2])
#     A = list(map(int, lines[4][5:-2].split(", ")))

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))
