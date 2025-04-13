from collections import defaultdict, deque
import sys
sys.setrecursionlimit(10**6)

n, m = map(int, input().split())
graph = defaultdict(list)
for _ in range(m):
    u, v = map(int, input().split())
    graph[u].append(v)
visited = [0] * (n + 1)

def dfs(u):
    visited[u] = 1  
    for v in graph[u]:
        if visited[v] == 0:
            if dfs(v):
                return True
        elif visited[v] == 1:
            return True  
    visited[u] = 2 
    return False

for i in range(1, n + 1):
    if visited[i] == 0:
        if dfs(i):
            print("YES")
            exit()
print("NO")

