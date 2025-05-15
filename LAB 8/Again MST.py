def make_set(n):
    parent = list(range(n + 1))
    rank = [1] * (n + 1)
    return parent, rank

def find(parent, i):
    if parent[i] != i:
        parent[i] = find(parent, parent[i])
    return parent[i]

def union(parent, rank, x, y):
    s1 = find(parent, x)
    s2 = find(parent, y)
    if s1 != s2:
        if rank[s1] < rank[s2]:
            parent[s1] = s2
        elif rank[s1] > rank[s2]:
            parent[s2] = s1
        else:
            parent[s2] = s1
            rank[s1] += 1
        return True
    return False

def kruskal(n, edges, include_edge=None, exclude_edge=None):
    parent, rank = make_set(n)
    total_cost = 0
    edges_used = []

    if include_edge is not None:
        u, v, w = include_edge
        if find(parent, u) != find(parent, v):
            union(parent, rank, u, v)
            total_cost += w
            edges_used.append((u, v, w))

    for edge in edges:
        u, v, w = edge
        if exclude_edge is not None and (u, v, w) == exclude_edge:
            continue
        if exclude_edge is not None and (v, u, w) == exclude_edge:
            continue
        if find(parent, u) != find(parent, v):
            union(parent, rank, u, v)
            total_cost += w
            edges_used.append((u, v, w))

    root = find(parent, 1)
    for i in range(2, n + 1):
        if find(parent, i) != root:
            return None, None
    return total_cost, edges_used

def find_second_mst(n, edges):
    edges_sorted = sorted(edges, key=lambda x: x[2])

    mst_cost, mst_edges = kruskal(n, edges_sorted)
    if mst_cost is None:
        return -1

    second_best = float('inf')

    for excluded_edge in mst_edges:
        current_cost, current_edges = kruskal(n, edges_sorted, exclude_edge=excluded_edge)
        if current_cost is not None and current_cost > mst_cost:
            if current_cost < second_best:
                second_best = current_cost

    adj = [[] for _ in range(n + 1)]
    for u, v, w in mst_edges:
        adj[u].append((v, w))
        adj[v].append((u, w))

    max_edge = [[0] * (n + 1) for _ in range(n + 1)]

    from collections import deque
    for start in range(1, n + 1):
        visited = [False] * (n + 1)
        q = deque()
        q.append((start, 0))
        visited[start] = True
        parent = [0] * (n + 1)
        parent_w = [0] * (n + 1)
        while q:
            u, p = q.popleft()
            for (v, w) in adj[u]:
                if not visited[v] and v != p:
                    visited[v] = True
                    parent[v] = u
                    parent_w[v] = w
                    q.append((v, u))
        for end in range(1, n + 1):
            if start == end:
                continue
            current = end
            max_w = 0
            while current != start:
                max_w = max(max_w, parent_w[current])
                current = parent[current]
            max_edge[start][end] = max_w

    for (u, v, w) in edges:
        if (u, v, w) not in mst_edges and (v, u, w) not in mst_edges:
            current_max = max_edge[u][v]
            new_cost = mst_cost + w - current_max
            if new_cost > mst_cost and new_cost < second_best:
                second_best = new_cost

    return second_best if second_best != float('inf') else -1


N, M = map(int, input().split())
edges = []
for _ in range(M):
    u, v, w = map(int, input().split())
    edges.append((u, v, w))

result = find_second_mst(N, edges)
print(result)
