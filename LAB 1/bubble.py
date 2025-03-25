def bubbleSort(arr):
    n = len(arr)
    for i in range(n - 1):
        flag = False  
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]: 
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                flag = True
        if not flag:  
            break
length = int(input())
arr = list(map(int, input().split()))
bubbleSort(arr)
print(" ".join(map(str, arr)))