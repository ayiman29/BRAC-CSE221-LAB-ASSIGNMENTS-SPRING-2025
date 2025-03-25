def twoSum(leng, sum, arr):
    i, j = 0, leng-1
    while i < j:
        if arr[i] + arr[j] == sum:
            return f"{i+1} {j+1}"
        elif arr[i] + arr[j] < sum:
            i += 1
        elif arr[i] + arr[j] > sum:
            j -= 1
    return -1

leng, sum = map(int, input().split())
arr = list(map(int, input().split()))
print(twoSum(leng, sum, arr))