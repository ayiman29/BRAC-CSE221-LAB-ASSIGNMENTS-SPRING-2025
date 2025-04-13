n = int(input())
adj_mat = [[0] * n for _ in range(n)]
for i in range(n):
    list1 = list(map(int, input().split()))
    for j in range(list1[0]):
        adj_mat[i][list1[j+1]] = 1

for row in adj_mat:
    print(' '.join(map(str, row)))
