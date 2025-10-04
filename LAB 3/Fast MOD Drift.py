def pow(a, b):
    ans = 1
    while b > 0:
        if b % 2 != 0:
            ans *= a
            b -= 1
        else:
            b = b//2
            a *= (a%107)

    return ans%107

a, b = map(int, input().split())
print(pow(a,b))