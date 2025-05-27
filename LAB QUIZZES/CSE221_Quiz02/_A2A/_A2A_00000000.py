# 00000000 10
# CSE-9B-9L-PC03 23301211
def solve(N, S, A):
    flag = False
    i, j = 0, len(A) - 1
    while i <= j:
        sum = A[i] + A[j]
        if sum == S:
            flag = True
            break
        if sum > S:
            j -= 1
        else:
            i += 1
    if flag == False:
        return (-1, -1)
    return (i + 1, j + 1)

