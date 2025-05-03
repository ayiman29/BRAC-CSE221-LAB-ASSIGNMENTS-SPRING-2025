from collections import defaultdict
import heapq

n, m = map(int, input().split())
graph = defaultdict(list)

for _ in range(m):
    u, v, w = map(int, input().split())
    u -= 1
    v -= 1
    graph[u].append((v, w))
    graph[v].append((u, w))

def minimize_danger(graph, start):
    danger = [float('inf')] * n
    danger[start] = 0
    heap = [(0, start)] 

    while heap:
        curr_danger, u = heapq.heappop(heap)

        if curr_danger > danger[u]:
            continue

        for v, w in graph[u]:
            max_danger = max(curr_danger, w) 
            if max_danger < danger[v]:
                danger[v] = max_danger
                heapq.heappush(heap, (danger[v], v))

    return danger

danger = minimize_danger(graph, 0)
print(' '.join(str(d if d != float('inf') else -1) for d in danger))

