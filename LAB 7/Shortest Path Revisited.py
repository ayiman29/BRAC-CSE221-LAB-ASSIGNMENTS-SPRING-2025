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
    graph[v].append((u, w))  
 
dist = [[float('inf'), float('inf')] for _ in range(n)]
dist[s][0] = 0
 
heap = [(0, s)]
 
while heap:
    cost, u = heapq.heappop(heap)
 
    for v, w in graph[u]:
        new_cost = cost + w
        if new_cost < dist[v][0]:
            dist[v][1] = dist[v][0]
            dist[v][0] = new_cost
            heapq.heappush(heap, (new_cost, v))
        elif dist[v][0] < new_cost < dist[v][1]:
            dist[v][1] = new_cost
            heapq.heappush(heap, (new_cost, v))
 
print(dist[d][1] if dist[d][1] != float('inf') else -1)