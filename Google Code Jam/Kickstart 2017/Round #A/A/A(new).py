def main_quare(n):
    tmp = (n*n+n)**2 + n*(n+1)*(2*n+1) + n*(n+1)
    return tmp//12

def new_column(n):
    return n + (n-1)*n*(n+1)//2 - n*(n+1)*(2*n+1)//6 + n*n

for tc in range(int(input())):
    r, c = map(int, input().split())
    #prototype: list/tuple/...= map(function_name, list)
    if (c < r):
        r, c = c, r
    r = r-1
    c = c-1
    ans = main_quare(r) + (c-r)*new_column(r) #r = min(r, c)
    print("Case #" + str(tc+1) + ": ")
    print(str(ans % 1000000007))
