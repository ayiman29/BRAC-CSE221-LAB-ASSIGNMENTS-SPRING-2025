# 00000000 10
# CSE-9B-9L-PC05 23301211
def solve(arr):
    for i in range(len(arr) - 1):
        flag = False
        for j in range(len(arr) - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                flag = True
        if flag == False:
            break
    return arr