def merge(leng1, leng2, arr1, arr2):
    i, j = 0, 0
    arr3 = []
    count = leng1+leng2
    while i != leng1 and j  != leng2:
        if arr1[i] <= arr2[j]:
            arr3.append(arr1[i])
            i += 1
            count += 1
        elif arr1[i] > arr2[j]:
            arr3.append(arr2[j])
            j += 1
            count += 1
    if count + 1 != len(arr3):
        if i == leng1:
            for j in range(j, leng2):
                arr3.append(arr2[j])
        else:
            for i in range(i, leng1):
                arr3.append(arr1[i])
    return arr3
leng1 = int(input())
arr1 = list(map(int, input().split()))
leng2 = int(input())
arr2 = list(map(int, input().split()))
arr3 = merge(leng1, leng2, arr1, arr2)
print(" ".join(map(str, arr3)))