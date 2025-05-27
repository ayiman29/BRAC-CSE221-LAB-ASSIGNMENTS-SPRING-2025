# 23301211 10
# CSE-9B-9L-PC02 23301211
def solve(n, initX, initY, arr):
    m = len(arr)
    ans = 0
    for i in range(initX-1, initX+2):
        for j in range(initY-1, initY+2):
            if (i, j) not in arr and i > 0 and i < n+1 and j >0 and j < n+1 and (i, j) != (initX, initY):
                ans += 1

    return ans

