from collections import deque
def solve(N, x1, y1, x2, y2):
    moves = [(2, 1), (2, -1), (-2, 1), (-2, 1,), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]
    dist= [[-1]*(N+1) for _ in range(N+1)]
    que = deque()
    dist[x1][y1] = 0
    que.append((x1, y1))
    while que:
        x, y = que.popleft()
        if (x, y) == (x2, y2):
            break
        for dx, dy in moves:
            nx, ny = x+dx, y+dy
            if 1 <= nx <= N and 1 <= ny <= N and dist[nx][ny] == -1:
                dist[nx][ny] = dist[x][y] + 1
                que.append((nx, ny))
    return(dist[x2][y2])
    


