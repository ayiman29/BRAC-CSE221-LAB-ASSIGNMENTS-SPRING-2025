from collections import defaultdict
import heapq

n, m, s, t = map(int, input().split())

s -= 1
t -= 1

graph = defaultdict(list)


for _ in range(m):
    u, v, w = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append((v, w))


def dijkstra(graph, s):
    dist = [float('inf')] * n
    parent = [None] * n
    heap = [(0, s)]
    dist[s] = 0

    while heap:
        curr_dist, u = heapq.heappop(heap)

        if curr_dist > dist[u]:
            continue 

        for v, w in graph[u]:
            if dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                parent[v] = u
                heapq.heappush(heap, (dist[v], v))


    return dist

dist_s = dijkstra(graph, s)
dist_t = dijkstra(graph, t)
time, node = float('inf'), None
for i in range(n):
    if dist_s[i] != float('inf') and dist_t[i] != float('inf'):
        curr = max(dist_s[i], dist_t[i])
        if curr < time:  
            time = curr
            node = i + 1

if node == None:
    print(-1)
else:
    print(time, node)
