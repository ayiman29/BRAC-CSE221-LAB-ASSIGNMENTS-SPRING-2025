import os, sys, ast, time, random, threading, subprocess
from collections import defaultdict
# Compile and run: pypy _A4D_Testing.py
def solve(N, edges):
    res = False
    degrees = {}
    for i in edges:
        u, v = i
        if u not in degrees.keys():
            degrees[u] = 0
        if v not in degrees.keys():
            degrees[v] = 0
        degrees[u] += 1
        degrees[v] += 1
    odd = 0
    for i in degrees.values():
        if i % 2 != 0:
            odd += 1
    if odd == 0 or odd == 2:
        return True
    print("odd:", odd)
    print(degrees)
    
    return res


# stdin
# 3 2
# 0 1
# 1 2

# N, M = map(int, input().split())
# edges = []
# for i in range(M):
#     u, v = map(int, input().split())
#     edges.append((u, v))

# # hardcoded input
#N = 5
#edges = [(0, 1), (0, 2), (0, 3), (2, 3), (2, 4), (3, 4)]
#N = 8
#edges = [(0, 2), (0, 4), (1, 0), (1, 4), (1, 6), (1, 5), (2, 4), (2, 5), (3, 2), (4, 3), (4, 7), (5, 3), (6, 4), (6, 2), (6, 5), (7, 0)]
N = 5
edges = [(0, 1), (0, 2), (0, 3), (0, 4), (1, 2), (1, 3), (2, 3), (2, 4), (3, 4)]
#start = time.time()
res = solve(N, edges)
#finish = time.time()
#elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

#print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
