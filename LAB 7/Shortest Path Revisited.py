from collections import defaultdict
import heapq

n, m, s, d = map(int, input().split())
s -= 1
d -= 1
graph = defaultdict(list)
for _ in range(m):
    u, v, w = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append((v, w))

