def selection(arr1, arr2, length):
    count = 0
    for i in range(length):
        max = arr2[i]
        max_idx = i
        flag = False
        for j in range(i+1, length):
            if arr2[j] > max:
                max = arr2[j]
                max_idx = j
                flag = True
            elif arr2[j] == max:
                if arr1[j] < arr1[max_idx]:
                    max_idx = j
                    flag = True
        if flag == True:
            arr2[i], arr2[max_idx] = arr2[max_idx], arr2[i]
            arr1[i], arr1[max_idx] = arr1[max_idx], arr1[i]

            count += 1
    return count

length = int(input())
arr1 = list(map(int, input().split()))
arr2 = list(map(int, input().split()))
swap_max = selection(arr1, arr2, length)
print("Minimum swaps:", swap_max)
for i in range(length):
    print(f"ID: {arr1[i]} Mark: {arr2[i]}")