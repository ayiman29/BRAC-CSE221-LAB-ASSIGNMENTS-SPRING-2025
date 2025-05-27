# 00000000 25
# CSE-9B-9L-PC03 23301211
def solve(list1, list2):
    N = len(list1)
    M = len(list2)
    k = N + M
    res = [None]*k
    idx = k - 1

    i = 0
    j = 0
    while i < N and j < M:
        if list1[i] <= list2[j]:
            res[idx] = list1[i]
            idx -= 1
            i += 1

        else:
            res[idx] = list2[j]
            idx -= 1
            j += 1
        if idx + 2 < k:

            if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1

    

    while i < N:
        res[idx] = list1[i]
        i += 1
        idx -= 1
        if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1
    while j < M:
        res[idx] = list2[j]
        j += 1
        idx -= 1
        if res[idx+1] == res[idx+2]:
                res[idx+1] = 0
                idx += 1
    res = res[idx+1::]

    
    
    return res