import os, sys, ast, time, random, threading, subprocess
# Compile and run: pypy _A6C_Testing.py
from collections import deque
def solve(N, x1, y1, x2, y2):
    '''
    N = int(input())
    x1, y1  = map(int, input().split())
    x2, y2  = map(int, input().split())
    '''
    moves = [(2, 1), (2, -1), (-2, 1), (-2, 1,), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]
    dist= [[-1]*(N+1) for _ in range(N+1)]
    que = deque()
    dist[x1][y1] = 0
    que.append((x1, y1))
    while que:
        #print(que)
        x, y = que.popleft()
        if (x, y) == (x2, y2):
            break
        for dx, dy in moves:
            nx, ny = x+dx, y+dy
            if 1 <= nx <= N and 1 <= ny <= N and dist[nx][ny] == -1:
                dist[nx][ny] = dist[x][y] + 1
                que.append((nx, ny))
    return(dist[x2][y2])


# stdin
# 4
# 1 1
# 3 4

# N = int(input())
# X1, Y1 = list(map(int, input().split()))
# X2, Y2 = list(map(int, input().split()))

# # hardcoded input
N = 3
X1 = 2
Y1 = 2
X2 = 1
Y2 = 3

start = time.time()
res = solve(N, X1, Y1, X2, Y2)
finish = time.time()
elapsed = finish - start

# # file output
# with open("OutputOfYourCode.txt", "w") as fout:
#     fout.write(str(res))

# stdout
print(res)

print("Execution time for the targeted one test is " + f"{elapsed:.9f}" + "s", flush=True)
os._exit(0)
