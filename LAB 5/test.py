from collections import defaultdict
import sys
sys.setrecursionlimit(10**6)  # Fix for RecursionError on deep graphs

def has_cycle(n, m, edges):
    graph = defaultdict(list)
    for u, v in edges:
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
                return True
    return False

# ---------- TEST CASES ----------
assert has_cycle(4, 4, [(1, 2), (2, 3), (3, 4), (4, 2)]) == True
assert has_cycle(4, 3, [(1, 2), (2, 3), (3, 4)]) == False
assert has_cycle(6, 5, [(1, 2), (2, 3), (4, 5), (5, 6), (6, 4)]) == True
assert has_cycle(6, 4, [(1, 2), (3, 4), (5, 6), (6, 3)]) == False
assert has_cycle(3, 1, [(1, 1)]) == True  # if self-loops allowed
assert has_cycle(5, 0, []) == False

edges = [(i, i + 1) for i in range(1, 100000)]
assert has_cycle(100000, 99999, edges) == False

edges = [(i, i + 1) for i in range(1, 100000)] + [(100000, 1)]
assert has_cycle(100000, 100000, edges) == True
