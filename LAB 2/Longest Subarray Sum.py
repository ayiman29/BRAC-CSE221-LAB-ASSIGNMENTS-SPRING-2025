def subarr(leng, sum, arr):
    i, j = 0, 0
    max = 0
    curr_sum = 0
    while i != leng:
        if i == j:
            curr_sum = arr[i]
            if curr_sum > sum:
                i += 1
                continue
        else:
            curr_sum += arr[j]
            sub = j - i
        if curr_sum > sum or j == leng - 1:
            sub = j - i
            if sub > max:
                max = sub
            i += 1
            j = i
            curr_sum = 0
        else:
            j += 1
    return max

leng, sum = map(int, input().split())
arr = list(map(int, input().split()))
print(subarr(leng, sum, arr))