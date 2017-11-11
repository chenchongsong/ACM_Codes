#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define maxn 500010
using namespace std;

int N, M;
int tot = 0;
int cnt[maxn];
long long sum[maxn];
int fa[maxn], idx[maxn];

int getf(int x) {
    return x == fa[x] ? x :(fa[x] = getf(fa[x]));
}
void Union(int u,int v) {
    int fu = getf(u);
    int fv = getf(v);
    fa[fu] = fv,sum[fv] += sum[fu];
    cnt[fv] += cnt[fu];
}
void Separate(int x) {
    int fx = getf(idx[x]);
    sum[fx] -= x,cnt[fx] --;
    idx[x] = ++tot;
    sum[idx[x]] = x,cnt[idx[x]] = 1, fa[idx[x]] = idx[x];
}
int main () {

    
    scanf("%d%d", &N, &M);
    for (int i = 0;i <= N;i ++)
        sum[i] = fa[i] = idx[i] = i,cnt[i] = 1;
    tot = N;
    for (int i=1; i<=M; i++) {
        
        int opt, a, b;
        scanf("%d", &opt);
            switch(opt) {
                case 1:
                    scanf("%d%d",&a,&b);
                    if (getf(idx[a]) != getf(idx[b]))
                        Union(idx[a],idx[b]);
                    break;
                case 2:
                    scanf("%d%d",&a,&b);
                    if (getf(idx[a])!= getf(idx[b]))
                        Separate(a),Union(idx[a],idx[b]);
                    break;
                case 3:
                    scanf ("%d",&a);
                    int af = getf(idx[a]);
                    printf ("%d %lld\n",cnt[af],sum[af]);
                break;
            }
    }
    return 0;
}