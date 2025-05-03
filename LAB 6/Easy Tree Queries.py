from collections import defaultdict
import sys
sys.setrecursionlimit(300000)
n, r = map(int, input().split())
graph = defaultdict(list)
for _ in range(n-1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

subcount = [0 for _ in range(n+1)]

def dfs(node, parent):
    subcount[node] = 1 
    for neighbor in graph[node]:
        if neighbor != parent:  
            dfs(neighbor, node)  
            subcount[node] += subcount[neighbor]  

dfs(r, -1)
q = int(input()) 
for _ in range(q):
    x = int(input()) 
    print(subcount[x]) 

