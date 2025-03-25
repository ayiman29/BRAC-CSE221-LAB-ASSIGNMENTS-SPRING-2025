def mergeSort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_arr = mergeSort(arr[0:mid])
    right_arr = mergeSort(arr[mid:])
    return merge(left_arr, right_arr)

def merge(left_arr, right_arr):
    m, n = len(left_arr), len(right_arr)
    i, j = 0, 0
    arr3 = []
    while i != m and j != n:
        if left_arr[i] <= right_arr[j]:
            arr3.append(left_arr[i])
            i += 1
        else:
            arr3.append(right_arr[j])
            j += 1
    for i in range(i, m):
        arr3.append(left_arr[i])
    for j in range(j, n):
        arr3.append(right_arr[j])
    return arr3
arr = [-3, -21, 5, -2, 52, 62, -114]
arr = mergeSort(arr)
print(arr)
