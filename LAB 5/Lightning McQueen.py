from collections import defaultdict, deque

n, m, s, d = map(int, input().split())
graph = defaultdict(list)

list1 = list(map(int, input().split()))
list2 = list(map(int, input().split()))
for u, v in zip(list1, list2):
    graph[u].append(v)
    graph[v].append(u)

for node in graph:
    graph[node].sort()

dist = {i: float('inf') for i in range(1, n + 1)}
parent = {i: -1 for i in range(1, n + 1)}
dist[s] = 0
parent[s] = None

q = deque([s])

def bfs():
    while q:
        curr = q.popleft()
        for neighbor in graph[curr]:
            if dist[neighbor] > dist[curr] + 1:
                dist[neighbor] = dist[curr] + 1
                parent[neighbor] = curr
                q.append(neighbor)

bfs() 

if dist[d] == float('inf'):
    print(-1)
else:
    path = []
    curr = d
    while curr is not None:
        path.append(curr)
        curr = parent[curr]
    print(len(path) - 1)
    print(*reversed(path))
