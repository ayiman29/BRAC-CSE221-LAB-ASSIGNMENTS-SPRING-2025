from math import gcd
n, k = map(int, input().split())
list1 = [[0] for _ in range(n+1)]
c = 1
for i in range(1, n+1):
    for j in range(1, n+1):
        if gcd(i, j) == 1 and i != j:
            list1[c].append(j)
    c += 1


for _ in range(k):
    x, y = map(int, input().split())
    if y < len(list1[x]):
        print(list1[x][y])
    else:
        print(-1)