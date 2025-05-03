from collections import defaultdict, deque

v, e = map(int, input().split())
graph = defaultdict(list)
in_degree = defaultdict(int)
for _ in range(e):
    a, b= map(int, input().split())
    graph[a].append(b)
    if a not in in_degree:
        in_degree[a] = 0


def topo_sort(graph):
    for i in graph.values():
        for j in i:
            in_degree[j] += 1

    queue = deque()
    for i in range(1, v + 1):
        if in_degree[i] == 0:
            queue.append(i)
    path = []
    while queue:
        curr = queue.popleft()
        path.append(curr)
        for i in graph[curr]:
            in_degree[i] -= 1
            if in_degree[i] == 0:
                queue.append(i)
    if len(path) != v:
        return [-1]
    else:
        return path

print(*topo_sort(graph))
