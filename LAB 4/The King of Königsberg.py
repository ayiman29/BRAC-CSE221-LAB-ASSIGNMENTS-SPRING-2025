size = int(input())
n, m = map(int, input().split())
list1 = []
for i in range(n-1, n+2):
    for j in range(m-1, m+2):
        if (i > 0 and i <= size and j > 0 and j <= size) and (i, j) != (n, m):
            list1.append((i, j)) 


print(len(list1))
for i in list1:
    print(i[0], i[1])
