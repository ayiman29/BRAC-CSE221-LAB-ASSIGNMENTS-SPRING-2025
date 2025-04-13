n, m = map(int, input().split())
adj_list = {i: 0 for i in range(1, n+1)}

u_list = list(map(int, input().split()))
v_list = list(map(int, input().split()))

for u, v in zip(u_list, v_list):
    adj_list[u] -= 1
    adj_list[v] += 1

print(*adj_list.values())