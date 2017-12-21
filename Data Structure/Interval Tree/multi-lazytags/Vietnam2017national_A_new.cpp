#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, m;
ll op, qL, qR; // 每次update或query前 都必须clarify
ll _sum;

const ll maxnode = 1<<17;

// specialised
ll sum[maxnode][4];

struct IntervalTree{
    ll addv[maxnode*4][4];
    ll sumv[maxnode*4];

    void add(ll &a, ll b){
        a = (a + b) % MOD;
        if (a < 0) a += MOD;
    }
    ll find_val(ll qL, ll k) {
        if (k == 0) return (-1LL*qL*qL*qL + 6*qL*qL - 11*qL + 6) % MOD;
        if (k == 1) return (3*qL*qL - 12*qL + 11) % MOD;
        if (k == 2) return -3*qL + 6;
        return 1;
    }

    void maintain(ll o, ll L, ll R) { // update sumv[]
        ll lc = o*2, rc = o*2+1;
        // sumv[o] = 0; // important !
        if (L < R) // if having children
            sumv[o] = (sumv[lc] + sumv[rc]) % MOD;
        for (int k=0; k<4; k++)
            add(sumv[o], addv[o][k] * (sum[R][k]-sum[L-1][k]+MOD));
    }
    void update(ll o, ll L, ll R, ll flag){ // flag = -1 or +1
        ll lc = o*2, rc = o*2+1;
        if (qL <= L && R <= qR) {
            for (int k=0; k<4; k++) {
                ll val = find_val(qL, k) * flag;
                add(addv[o][k], val);
            }
        }
        else {
            ll M = L + (R-L)/2;
            if(qL <= M) update(lc, L, M, flag);
            if(qR > M) update(rc, M+1, R, flag);
        }
        maintain(o, L, R);
    }
    void query(ll o, ll L, ll R, vector<ll> _adds) {
        if (qL <= L && R <= qR) { //当前区间完全包含于询问中
            add(_sum, sumv[o]);
            for (int k = 0; k < 4; k++)
                add(_sum, _adds[k] * (sum[R][k]-sum[L-1][k]+MOD));
        }
        else {
            ll lc = o*2, rc = o*2+1;
            ll M = L + (R-L)/2;
            for (int k = 0; k < 4; k++)
                _adds[k] = (_adds[k] + addv[o][k]) % MOD;

            if(qL <= M) query(lc, L, M, _adds);
            if(qR > M) query(rc, M+1, R, _adds);
        }
    } 
} tree;

int main(){
    cin >> n >> m;
    memset(&tree, 0, sizeof(tree));

    for (ll i=1; i<=n; i++) {
        sum[i][0] = sum[i-1][0] + 1LL;
        sum[i][1] = (sum[i-1][1] + i) % MOD;
        sum[i][2] = (sum[i-1][2] + i*i) % MOD;
        sum[i][3] = (sum[i-1][3] + i*i*i) % MOD;
    }
    // sum[x][k] = 1^k + 2^k + 3^k + ... + x^k

    vector<ll> zeros(4);
    while(m--) {
        scanf("%lld%lld%lld", &op, &qL, &qR);

        if (op == 0) {
            _sum = 0;
            tree.query(1, 1, n, zeros);
            printf("%lld\n", _sum);
        }
        else if (op == 1) tree.update(1, 1, n, 1);
        else if (op == 2) tree.update(1, 1, n, -1); 
    }
    return 0;
}