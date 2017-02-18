#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <set>
 
using namespace std;
typedef long long LL;
inline void read(int &x){x=0;char c;while((c=getchar())<'0'||c>'9');for(x=c-'0';(c=getchar())>='0'&&c<='9';x=x*10+c-'0');}
 
const int inf = 0x3f3f3f3f ;
const int N = 3e5 + 10 ;
 
struct Info
{
    int l, w;
 
    inline bool operator < (const Info & b) const
    {
        return l < b.l;
    }
} p[N];
 
multiset<int> H;
int n, m, cnt;
 
int main()
{
    #ifdef LX_JUDGE
    freopen("in.txt", "r", stdin);
    #endif
 
    read(n), read(m);
    for (int i = 1; i <= n; ++i) 
        read(p[i].l), read(p[i].w);
 
    sort(p + 1, p + n + 1);
 
    for (int i = 1; i <= n; ++i)
    {
        set<int>::iterator it = H.lower_bound(p[i].l - m);
        if (it != H.end() && (*it) <= p[i].l) ++cnt, H.erase(it);
        H.insert(p[i].l + p[i].w);
    }
 
    printf("%d\n", cnt);
 
    return 0;
}