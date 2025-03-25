def pair(arr, left, right):
    if left == right:
        return float('-inf')  

    if left + 1 == right:
        return arr[left] + arr[right] ** 2  

    mid = (left + right) // 2
    best_left = pair(arr, left, mid)  
    best_right = pair(arr, mid + 1, right)  


    max_left = max(arr[left:mid+1])  
    max_right = max(abs(x) for x in arr[mid+1:right+1])   
    cross = max_left + (max_right ** 2)  

    return max(best_left, best_right, cross)

n = int(input())
arr = list(map(int, input().split()))
print(pair(arr, 0, n - 1))