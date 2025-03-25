import sys

t = int(sys.stdin.readline().strip()) 
results = [] 
for _ in range(t):
    datas = sys.stdin.readline().strip().split()  
    val_1, sign, val_2 = int(datas[1]), datas[2], int(datas[3]) 

    if sign == "+":
        val = val_1 + val_2
    elif sign == "-":
        val = val_1 - val_2
    elif sign == "*":
        val = val_1 * val_2
    elif sign == "/":
        val = val_1 / val_2 
    else:
        raise ValueError(f"Unknown operator: {sign}")  

    results.append(f"{val:.6f}")  

sys.stdout.write("\n".join(results) + "\n")  
