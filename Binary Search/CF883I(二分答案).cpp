#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#define maxn 300010
#define INF 1e9 + 100
// typedef long long ll;
using namespace std;
int a[maxn];
int n, k, m;
int sum[maxn];

bool check(int delta) {
    // memset(sum, 0, sizeof(sum));
    sum[0] = 0;
    for (int i=1; i<=n; i++) {
        int pos1 = lower_bound(a+1, a+i, a[i]-delta) - a;
        int pos2 = i-k+1;

        int flag = 1;
        if (pos1 > pos2) flag = 0;
        else {
            int cnt = sum[pos2-1] - sum[pos1-2];
            if (cnt <=0 && pos1 != 1)
                flag = 0;
        }

        sum[i] = sum[i-1] + flag;
        if (i == n)
            return (flag);
    }
    return false; // useless
}

int main()
{
    cin >> n >> k;
    for (int i=1; i<=n; i++) cin >> a[i];
    sort(a+1, a+n+1);
    if (k == 1) {puts("0"); return 0;}
    
    int l = -1, r = INF, mid;
    while (l + 1 < r)
        if (check(mid = l+(r-l)/2))
            r = mid;
        else
            l = mid;
    
    cout << r << endl;
    return 0;
}

/*

9 3
10 20 30 90 100 120 130 140 150

9 3
1000000 2000000 3000000 9000000 10000000 12000000 13000000 14000000 15000000

3000000

6 3
10 10 40 40 40 100
*/
