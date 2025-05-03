from collections import defaultdict
import heapq


n, m, s, d = map(int, input().split())
s -= 1
d -= 1
w = list(map(int, input().split()))
graph = defaultdict(list)
for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append((v))

def dijkstra(graph, s, d):
    dist = [float('inf')] * n
    dist[s] = w[s] 
    heap = [(w[s], s)]

    while heap:
        curr_dist, u = heapq.heappop(heap)

        if curr_dist > dist[u]:
            continue

        for v in graph[u]:
            cost = curr_dist + w[v]
            if dist[v] > cost:
                dist[v] = cost
                heapq.heappush(heap, (cost, v))

    return dist[d] if dist[d] != float('inf') else -1

print(dijkstra(graph, s, d))