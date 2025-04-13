n, m = map(int, input().split())
adj_list = {i: [] for i in range(1, n+1)}

u_list = list(map(int, input().split()))
v_list = list(map(int, input().split()))
w_list = list(map(int, input().split()))

for u, v, w in zip(u_list, v_list, w_list):
    adj_list[u].append((v, w))

for key in range(1, n+1):
    if adj_list[key]:
        print(f"{key}: ", end="")
        print(" ".join(f"({v},{w})" for v, w in adj_list[key]))
    else:
        print(f"{key}:")