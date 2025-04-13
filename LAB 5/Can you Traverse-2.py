from collections import defaultdict
import sys
sys.setrecursionlimit(2*100000+5)
graph = defaultdict(list)
n, m = map(int, input().split())
list1 = list(map(int, input().split()))
list2 = list(map(int, input().split()))
for u, v in zip(list1, list2):
    graph[u].append(v)
    graph[v].append(u)
 
for node in graph:
    graph[node].sort()
 
 
def dfs(tree, node, path = None, seen=None):
    if seen is None:
        seen = set() 
    if path is None:
        path = []
    seen.add(node)
    path.append(node)    
  
    for child in tree[node]:  
        if child not in seen:
            dfs(tree, child, path, seen)
    return path
 
 
print(*dfs(graph, 1))
