n = int(input())
cnt = dict()
suma = 0
ans = 0
a = list(map(int, input().split()))
for i in range(0, n):
    y = a[i]
    ans += y * i - suma;
    ans -= cnt.get(y - 1, 0)
    ans += cnt.get(y + 1, 0)
    suma += y
    cnt[a[i]] = cnt.get(y, 0) + 1
print(ans)
