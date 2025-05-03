from collections import defaultdict, deque

n, m = map(int, input().split())
graph = defaultdict(list)
for _ in range(m):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

def bfs(graph, source=1):
    path = []            
    visited = set()    
    que = deque()
    que.append(source)
    visited.add(source)

    while que: 
        curr = que.popleft()
        path.append(curr)

        for neighbor in sorted(graph[curr]):
            if neighbor not in visited:
                que.append(neighbor)
                visited.add(neighbor)

    return path

result = bfs(graph)
print(*result)
