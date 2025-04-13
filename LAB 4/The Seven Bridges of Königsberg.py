# RULE:
# 1) No. of odd-degree nodes can be 0 or 2
# 2) Graph must be connected
#DOESN'T WORK
n, m = map(int, input().split())

u_list = list(map(int, input().split())) 
v_list = list(map(int, input().split()))  


nodes = set(u_list + v_list)
adj_list = {i: set() for i in nodes}




for u, v in zip(u_list, v_list):
    adj_list[u].add(v)  
    adj_list[v].add(u) 



odd = 0
for i, j in adj_list.items():
    if len(j) % 2 != 0:
        odd += 1
if odd == 2 or odd == 0:
    print("YES")
else:
    print("NO")