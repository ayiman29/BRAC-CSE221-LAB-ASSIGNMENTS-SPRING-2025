# 23301211 100
# CSE-9B-9L-PC02 23301211
from collections import defaultdict
def solve(N, edges):
    res = False
    degrees = {}
    for i in edges:
        u, v = i
        if u not in degrees.keys():
            degrees[u] = 0
        if v not in degrees.keys():
            degrees[v] = 0
        degrees[u] += 1
        degrees[v] += 1
    odd = 0
    for i in degrees.values():
        if i % 2 != 0:
            odd += 1
    if odd == 0 or odd == 2:
        return True
    
    return res