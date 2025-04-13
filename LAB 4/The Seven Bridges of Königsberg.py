N, M = map(int, input().split())
u = list(map(int, input().split()))
v = list(map(int, input().split()))

degree = [0] * (N + 1)

for i in range(M):
    degree[u[i]] += 1
    degree[v[i]] += 1

odd_count = sum(1 for d in degree if d % 2 != 0)

print("YES" if odd_count == 0 or odd_count == 2 else "NO")


