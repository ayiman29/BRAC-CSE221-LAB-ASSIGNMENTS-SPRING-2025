def binary(base2, low, high, val = -1):
    if high >= low:
        mid = low + (high - low) // 2
        if base2[mid] == "1":
            val = mid+1
            return binary(base2, low, mid-1, val)
        else:
            return binary(base2, mid+1, high, val)
    else:
        return val
    
n = int(input())
for _ in range(n):
    num = input()
    print(binary(num, 0, len(num)-1))