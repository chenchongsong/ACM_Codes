#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN =  1000000 + 2;
typedef long long ll;

struct Lines {ll l,r,v;} lines[MAXN];
bool cmp(Line a, Line b) {return a.r < b.r;}

int find(int x)  //二分 找出第一个右端点 小于 当前线段x左端点的 线段
{
    int l = 0, r = x, mid = 0;
    while( r-l > 1)
    {
        mid = (l + r) >> 1;
        if (lines[mid].r <= lines[x].l) 
            l = mid;
        else 
            r = mid;
    }
    return l;
}
ll f[MAXN];

int main()
{
    int n = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld%lld%lld", &lines[i].l, &lines[i].r, &lines[i].v);
    sort(lines + 1, lines + n + 1,cmp);
    for(int i = 1; i <= n; ++i)
        f[i] = max(f[i - 1], f[find(i)] + lines[i].v);
    printf("%lld", f[n]);


    //printf ("%d -- %d -- %d\n", find(1), find(2), find(3));
    return 0;
}