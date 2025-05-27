import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _A7E_Testing.py
import heapq
def solve(N, M, Us, Vs, Ws):
    res = -1
    # your code here
    return res

# stdin
# 4 3
# 1 4 3
# 3 4 4
# 2 3 5

# N, M = map(int, input().split())
# Us, Vs, Ws = [], [], []
# for _ in range(M):
#     u, v, w = map(int, input().split())
#     Us.append(u)
#     Vs.append(v)
#     Ws.append(w)

# # hardcoded input
N, M = 4, 3
Us = [1, 3, 2]
Vs = [4, 4, 3]
Ws = [3, 4, 5]
start = time.time()
res = solve(N, M, Us, Vs, Ws)
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
