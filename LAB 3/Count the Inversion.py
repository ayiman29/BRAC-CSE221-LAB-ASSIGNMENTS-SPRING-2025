def mergeSort(arr, left, right):
    count = 0
    if left < right:

        mid = (left + right) // 2
        count += mergeSort(arr, left, mid)  
        count += mergeSort(arr, mid + 1, right)  
        count += merge(arr, left, mid, right) 
    return count

def merge(arr, left, mid, right):
    count = 0
    temp = [] 
    i, j = left, mid + 1

    while i <= mid and j <= right:
        if arr[i] <= arr[j]:
            temp.append(arr[i])
            i += 1
        else:
            temp.append(arr[j])
            j += 1
            count += (mid - i + 1)
    

    while i <= mid:
        temp.append(arr[i])
        i += 1
    while j <= right:
        temp.append(arr[j])
        j += 1
    for k in range(len(temp)):
        arr[left + k] = temp[k]

    return count

n = int(input())
arr = list(map(int, input().split()))
print(mergeSort(arr, 0, n - 1))
print(" ".join(map(str, arr))) 