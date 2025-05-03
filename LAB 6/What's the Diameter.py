from collections import defaultdict, deque

n = int(input())
graph = defaultdict(list)
for _ in range(n-1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

def bfs(graph, source):
    lvl = defaultdict(int)
    visited = set()
    lvl[source] = 0
    visited.add(source)
    queue = deque([source])
    
    farthest_node = source
    max_distance = 0

    while queue:
        curr = queue.popleft()
        for i in graph[curr]:
            if i not in visited:
                visited.add(i)
                lvl[i] = lvl[curr] + 1
                queue.append(i)
                if lvl[i] > max_distance:
                    max_distance = lvl[i]
                    farthest_node = i

    return farthest_node, max_distance

fin, _ = bfs(graph, 1)
start, dist = bfs(graph, fin)

print(dist)
print(fin, start)


