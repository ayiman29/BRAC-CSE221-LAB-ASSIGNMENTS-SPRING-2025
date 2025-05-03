from collections import deque, defaultdict
import heapq  
x = int(input())
items = [input() for _ in range(x)]

graph = defaultdict(list)
in_degree = defaultdict(int)
all = set()


for i in range(len(items) - 1):
    if len(items[i]) > len(items[i+1]) and items[i].startswith(items[i+1]):
        print(-1)
        exit()
    
    flag = False
    for j in range(min(len(items[i]), len(items[i + 1]))):
        if items[i][j] != items[i + 1][j]:
            graph[items[i][j]].append(items[i + 1][j])
            in_degree[items[i + 1][j]] += 1
            flag = True
            break

for word in items:
    for c in word:
        all.add(c)


min_heap = []

for char in all:
    if in_degree[char] == 0:
        heapq.heappush(min_heap, char)


result = []

while min_heap:
    char = heapq.heappop(min_heap)
    result.append(char)
    
    for neighbor in graph[char]:
        in_degree[neighbor] -= 1
        
        if in_degree[neighbor] == 0:
            heapq.heappush(min_heap, neighbor)

if len(result) != len(all):
    print(-1)
else:
    print("".join(result))