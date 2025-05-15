def find(x):
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root
 
def union(x, y):
    root_x = find(x)
    root_y = find(y)
    if root_x != root_y:
        if size[root_x] < size[root_y]:
            root_x, root_y = root_y, root_x
        parent[root_y] = root_x
        size[root_x] += size[root_y]
    return size[root_x]
 
N, K = map(int, input().split())
 
parent = [i for i in range(N + 1)]
size = [1] * (N + 1)
 
for _ in range(K):
    a, b = map(int, input().split())
    print(union(a, b))



