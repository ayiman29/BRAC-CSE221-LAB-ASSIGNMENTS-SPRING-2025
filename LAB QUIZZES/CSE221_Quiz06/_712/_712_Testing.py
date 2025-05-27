import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _712_Testing.py

from collections import defaultdict
def solve(N, M, S, D, K, edges):
    res = 0
    graph = defaultdict(list)
    for i in edges:
        u, v, w = i
        graph[u].append((v, w))
        graph[v].append((u, w))
    

    return res


# stdin
# 7 10 3 7 5
# 2 3 1
# 2 4 1
# 4 3 6
# 4 1 2
# 1 7 2
# 4 5 3
# 5 7 8
# 4 7 1
# 5 6 4
# 6 7 2


N, M, S, D, K = map(int, input().split())

edges = []
u = []
v = []
w = []
for i in range(M):
    uu, vv, ww = map(int, input().split())
    u.append(uu)
    v.append(vv)
    w.append(ww)

for i in range(M):
    edges.append((u[i], v[i], w[i]))

start = time.time()
res = solve(N, M, S, D, K, edges)
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
