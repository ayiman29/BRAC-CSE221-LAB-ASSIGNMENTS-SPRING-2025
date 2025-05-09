from collections import defaultdict
import heapq
 
n, m, s, d = map(int, input().split())
s -= 1
d -= 1
 
list1 = list(map(int, input().split()))
list2 = list(map(int, input().split()))
list3 = list(map(int, input().split()))
 
list1 = [x - 1 for x in list1]
list2 = [x - 1 for x in list2]
 
graph = defaultdict(list)
for i in range(m):
    graph[list1[i]].append((list2[i], list3[i]))
 
def dijkstra(graph, s, d):
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
 
    if dist[d] == float('inf'):
        return -1, []
 
    path = []
    cur = d
    while cur is not None:
        path.append(cur+1)
        cur = parent[cur]
    path.reverse()
 
    return dist, path
 
dist, path = dijkstra(graph, s, d)
print(dist[d] if dist != -1 else -1)
if len(path) != 0:
    print(*path)