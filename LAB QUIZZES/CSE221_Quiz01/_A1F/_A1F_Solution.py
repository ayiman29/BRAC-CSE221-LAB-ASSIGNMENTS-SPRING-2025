def solve(sIDs, sMarks):
    N = len(sIDs)
    cnt = 0
    arr = []
    for i in range(N):
        max_idx = i
        max = sMarks[i]
        flag = False
        for j in range(i+1, N):
            if sMarks[j] > max:
                max_idx = j
                max = sMarks[j]
                flag = True
            elif sMarks[j] == max:
                if sIDs[j]<sIDs[max_idx]:
                    max_idx = j
                    flag = True
        if flag == True:
            sMarks[i], sMarks[max_idx] = sMarks[max_idx], sMarks[i]
            sIDs[i], sIDs[max_idx] = sIDs[max_idx], sIDs[i]
            cnt += 1  
    for i, j in zip(sIDs, sMarks):
        id, mark = i, j
        arr.append((id, mark))
    return (cnt, arr)