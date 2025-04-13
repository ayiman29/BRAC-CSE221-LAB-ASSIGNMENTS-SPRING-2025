from collections import defaultdict, deque

n, m, s, d, k = map(int, input().split())
graph = defaultdict(list)
for _ in range(m):
    u, v = map(int, input().split())
    graph[u].append(v)

for node in graph:
    graph[node].sort()  

def bfs(start):
    dist = {i: float('inf') for i in range(1, n + 1)}
    parent = {i: -1 for i in range(1, n + 1)}
    dist[start] = 0
    parent[start] = None
    q = deque([start])

    while q:
        curr = q.popleft()
        for neighbor in graph[curr]:
            if dist[neighbor] > dist[curr] + 1:
                dist[neighbor] = dist[curr] + 1
                parent[neighbor] = curr
                q.append(neighbor)

    return dist, parent


dist1, parent1 = bfs(s)
if dist1[k] == float('inf'):
    print(-1)
    exit()


path1 = []
curr = k
while curr is not None:
    path1.append(curr)
    curr = parent1[curr]
path1.reverse()


dist2, parent2 = bfs(k)
if dist2[d] == float('inf'):
    print(-1)
    exit()


path2 = []
curr = d
while curr is not None:
    path2.append(curr)
    curr = parent2[curr]
path2.reverse()


full_path = path1 + path2[1:]

print(len(full_path) - 1)
print(*full_path)
