def longest_subarray(N, K, arr):
    i = 0
    sum = 0
    maximum = 0

    for j in range(N):
        sum += arr[j]

        while sum > K and i <= j:
            sum -= arr[i]
            i += 1

        maximum = max(maximum, j - i + 1)

    return maximum


leng, k = map(int, input().split())
arr = list(map(int, input().split()))
print(longest_subarray(leng, k, arr))