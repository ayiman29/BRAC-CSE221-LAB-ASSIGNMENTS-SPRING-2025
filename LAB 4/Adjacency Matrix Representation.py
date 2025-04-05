n, m = map(int, input().split())
mat = [[0] * n for _ in range(n)]

for _ in range(m):
    u, v, w = map(int, input().split())
    mat[u-1][v-1] = w

for row in mat:
    print(' '.join(map(str, row)))
