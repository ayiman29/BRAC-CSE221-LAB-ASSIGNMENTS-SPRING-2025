from collections import defaultdict, deque
def solve(N, R, edges):
    res = [0] * (N + 1)
    graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
    def dfs(node, parent):
        res[node] = 1
        for n in graph[node]:
            if n != parent:
                dfs(n, node)
                res[node] += res[n]
    dfs(R, -1)
    return  res
