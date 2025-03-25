n = int(input())  
in_order = list(map(int, input().split()))  
pre_order = list(map(int, input().split()))  

def post_order(in_order, pre_order):
    if not in_order:
        return []
    
    root = pre_order[0]  
    
    root_idx = in_order.index(root)  

    left_subtree = post_order(in_order[:root_idx], pre_order[1:root_idx+1])
    right_subtree = post_order(in_order[root_idx+1:], pre_order[root_idx+1:])
    
    return left_subtree + right_subtree + [root]  


print(*post_order(in_order, pre_order))
