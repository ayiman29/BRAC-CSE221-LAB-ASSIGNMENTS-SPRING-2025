import sys
sys.setrecursionlimit(10**6)
ROW, COLUMN = map(int, input().split())
grid = [list(input().strip()) for _ in range(ROW)]
visited = [[False for _ in range(COLUMN)] for _ in range(ROW)]

def TDiamondM(grid, visited, r, c):
    if r < 0 or r >= ROW or c < 0 or c >= COLUMN or visited[r][c] or grid[r][c] == "#":
        return 0
    visited[r][c] = True
    count = 1 if grid[r][c] == "D" else 0

    count += TDiamondM(grid, visited, r + 1, c)  
    count += TDiamondM(grid, visited, r - 1, c) 
    count += TDiamondM(grid, visited, r, c + 1)  
    count += TDiamondM(grid, visited, r, c - 1)
    return count


max_diamonds = 0
for i in range(ROW):
    for j in range(COLUMN):
        if grid[i][j] != "#" and not visited[i][j]:  
            max_diamonds = max(max_diamonds, TDiamondM(grid, visited, i, j))

print(max_diamonds)
