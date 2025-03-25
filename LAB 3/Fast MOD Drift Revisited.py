def pow(a, n, m):
    ans = 1
    a = a % m 
    while n > 0:
        if n % 2 != 0: 
            ans = (ans * a) % m
        a = (a * a) % m  
        n //= 2
    return ans

def powsum(a, n, m):
    if n == 0:
        return 0
    if n == 1:
        return a % m  
    
    mid = n // 2
    s = powsum(a, mid, m)  
    pow_mid = pow(a, mid, m)  
    
    if n % 2 == 0:
        return (s + (pow_mid * s) % m) % m
    else:
        return (s + (pow_mid * s) % m + pow(a, n, m)) % m  



T = int(input())
for _ in range(T):
    a, n, m = map(int, input().split())
    print(powsum(a, n, m))
