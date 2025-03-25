def build_balanced_bst(arr, left, right, result):
    if left > right:
        return
    mid = (left + right) // 2  
    result.append(arr[mid])  
    build_balanced_bst(arr, left, mid - 1, result)  
    build_balanced_bst(arr, mid + 1, right, result)  


n = int(input())  
arr = list(map(int, input().split()))  
result = []
build_balanced_bst(arr, 0, n - 1, result)
print(*result)  

