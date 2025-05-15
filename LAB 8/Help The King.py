def find(x):
    while parent[x] != x:
        parent[x] = parent[parent[x]]  
        x = parent[x]
    return x
 
def union(x, y):
    root_x = find(x)
    root_y = find(y)
    if root_x == root_y:
        return False
    if size[root_x] < size[root_y]:
        root_x, root_y = root_y, root_x
    parent[root_y] = root_x
    size[root_x] += size[root_y]
    return True
 
 
n, m = map(int, input().split())
 
edges = []
for _ in range(m):
    u, v, w = map(int, input().split())
    edges.append((w, u, v))
 
edges.sort()  
 
parent = [i for i in range(n + 1)]
size = [1] * (n + 1)
 
total_cost = 0
for w, u, v in edges:
    if union(u, v):
        total_cost += w
 
print(total_cost)
