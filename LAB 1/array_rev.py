length, k = map(int, input().split())
arr = list(map(int, input().split()))
outarr = [0]*k

for i in range(0, k):
    outarr[(k-1)-i] = arr[i]
print(" ".join(map(str, outarr)))