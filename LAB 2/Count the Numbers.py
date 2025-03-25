def lower_bound(arr, low, high, x, val = -1):
    if high >= low:
        mid = low + (high - low) // 2
        if arr[mid] >= x:
            val = mid
            return lower_bound(arr, low, mid-1, x, val)
        else:
            return lower_bound(arr, mid+1, high, x, val)
    return val 

def upper_bound(arr, low, high, x, val = -1):
    if high >= low:
        mid = low + (high - low) // 2
        if arr[mid] <= x:
            val = mid 
            return upper_bound(arr, mid+1, high, x, val)
        else:
            return upper_bound(arr, low, mid-1, x, val)
    return val

leng, n = map(int, input().split())
arr = list(map(int, input().split()))
for i in range(n):
    lower, upper = map(int, input().split())
    upper_b = upper_bound(arr, 0, leng-1, upper) 
    lower_b = lower_bound(arr, 0, leng-1, lower) 
    if lower_b == -1 or upper_b == -1:
        print(0)
    else:
        print(upper_b - lower_b + 1)


