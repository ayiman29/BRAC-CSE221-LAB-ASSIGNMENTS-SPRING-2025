from collections import defaultdict
import heapq

n, m = map(int, input().split())

u = list(map(int, input().split()))
v = list(map(int, input().split()))
w = list(map(int, input().split()))

graph = defaultdict(list)
for i in range(m):
    graph[u[i] - 1].append((v[i] - 1, w[i]))
    
dist = [[float('inf'), float('inf')] for _ in range(n)]
heap = []

for to, weight in graph[0]:
    parity = weight % 2
    dist[to][parity] = weight
    heapq.heappush(heap, (weight, to, parity)) 

while heap:
    d, u, last_parity = heapq.heappop(heap)

    if d > dist[u][last_parity]:
        continue

    for v, w in graph[u]:
        p = w % 2
        if p != last_parity:
            if dist[v][p] > d + w:
                dist[v][p] = d + w
                heapq.heappush(heap, (dist[v][p], v, p))

ans = min(dist[n - 1])
print(ans if ans != float('inf') else -1)

