# 23301211 0
# CSE-9B-9L-PC13 1000055015
from collections import defaultdict
import random
def solve(N, M, S, D, K, edges):
    res = random.randint(0,10)
    graph = defaultdict(list)
    for i in edges:
        u, v, w = i
        graph[u].append((v, w))
        graph[v].append((u, w))
    

    return res