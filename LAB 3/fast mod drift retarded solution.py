def pow(a, n, m):
    ans = 1
    while n > 0:
        if n % 2 != 0:
            ans *= a
            n -= 1
        else:
            n = n//2
            a *= (a%m)

    return ans%m

def powsum(a, n, m):
    if n == 0:
        return 0
    mid = n // 2
    s = powsum(a, mid, m)
    if n % 2 == 0:
        ans = s
    else:
        ans= s + pow(a, n+1, m)
    return (s+pow(a, mid,m)*s)

a, n, m = map(int, input().split())
print(powsum(a, n, m))