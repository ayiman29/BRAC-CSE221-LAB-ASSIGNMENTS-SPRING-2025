from collections import defaultdict, deque

n, m = map(int, input().split())
graph = defaultdict(list)
for _ in range(m):
    i, j = map(int, input().split())
    graph[i].append(j)
    graph[j].append(i) 

def bipar(graph):
    color = {i: -1 for i in range(1, n + 1)}
    queue = deque()
    ans = 0

    for node in range(1, n + 1):   
        if color[node] == -1:
            zeros = 0
            ones = 0
            queue.append(node)
            color[node] = 1
            ones += 1

            while queue:
                curr = queue.popleft()
                for i in graph[curr]:
                    if color[i] == -1:
                        if color[curr] == 1:
                            color[i] = 0
                            zeros += 1
                        elif color[curr] == 0:
                            color[i] = 1
                            ones += 1
                        queue.append(i)
            ans += max(zeros, ones)  

    return ans

print(bipar(graph))