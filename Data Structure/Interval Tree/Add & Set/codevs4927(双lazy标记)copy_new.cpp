// 特色 修改了Query部分
// 不再需要传累加参数"add"
// 潜在优势：易于支持 multiple lazy tags (多重addv)
// 已AC
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#define ll long long
using namespace std;

ll n, m;
ll op, qL, qR, v; // 每次update或query前 都必须clarify
ll _sum, _min, _max;

const ll maxnode = 1<<17;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct IntervalTree{
ll addv[maxnode*4],setv[maxnode*4];
ll sumv[maxnode*4],minv[maxnode*4];
ll maxv[maxnode*4];

void maintain(ll o, ll L, ll R){
        ll lc = o*2, rc = o*2+1;
        if(L < R){
            sumv[o] = sumv[lc] + sumv[rc];
            maxv[o] = max(maxv[lc], maxv[rc]);
            minv[o] = min(minv[lc], minv[rc]);
        }
        if(setv[o] >= 0){
//when set included
            minv[o] = maxv[o] = setv[o];
            sumv[o] = setv[o] * (R-L+1);
        }
        if(addv[o]){
            minv[o] += addv[o];
            maxv[o] += addv[o];
            sumv[o] += addv[o] * (R-L+1);
        }
}
void pushdown(ll o){  // when set
        ll lc = o*2, rc = o*2+1;
        if(setv[o] >= 0){
            setv[lc] = setv[rc] = setv[o];
            addv[lc] = addv[rc] = 0;
            setv[o] = -1;
        }
        if(addv[o]){
            addv[lc] += addv[o];
            addv[rc] += addv[o];
            addv[o] = 0;
        }
    }
    void update(ll o, ll L, ll R){
        ll lc = o*2, rc = o*2+1;
        if(qL <= L && qR >= R){
            if(op == 2) { // set
                setv[o] = v;
                addv[o] = 0;
            } 
            else { //op==1 :Add
                addv[o] += v;
            }
        }
        else{
            pushdown(o);  //when set
            ll M = L + (R-L)/2;
            if(qL <= M) update(lc, L, M);
            else maintain(lc, L, M); //when set
            if(qR > M) update(rc, M+1, R);
            else maintain(rc, M+1, R);//when set
        }
        maintain(o, L, R);
    }
    void query(ll o, ll L, ll R){
//只需要set时可以删去第四个参数
        if(setv[o] >= 0){ // when set included
            ll v = setv[o] + addv[o];
            _sum += v * (min(R, qR)-max(L, qL)+1);
            _max = max(_max, v);
            _min = min(_min, v);
        }
        else if(qL <= L && qR >= R){
//当前区间完全包含于询问中
            _sum += sumv[o];
            _max = max(_max, maxv[o]);
            _min = min(_min, minv[o]);
        }
        else {
            ll lc = o*2, rc = o*2+1;
            ll M = L + (R-L)/2;
            pushdown(o);
            maintain(lc, L, M); //下面可能要用到sumv[lc]所以在subquery前就要maintain
            maintain(rc, M+1, R);
            if(qL <= M) query(lc, L, M);
            if(qR > M) query(rc, M+1, R);
        }
        maintain(o, L, R);
    } 
} tree;


int main(){
    scanf("%lld%lld",&n,&m);

    memset(&tree, 0, sizeof(tree));
    memset(tree.setv, -1, sizeof(tree.setv));
    tree.setv[1] = 0;/// wrong answer point

    for (ll i=1; i<=n; i++) {
        scanf("%lld", &v);
        qL = qR = i;
        op = 1;
        tree.update(1, 1, n);
    }

    while(m--){
        string s;
        cin >> s;
        // scanf("%d%d%d%d%d",&op,&x1,&qL,&x2,&qR);
        if (s == "add") {
            scanf("%lld%lld%lld",&qL,&qR,&v);
            op = 1;
            tree.update(1, 1, n);
        }
        if (s == "set") {
            scanf("%lld%lld%lld",&qL,&qR,&v);
            op = 2;
            tree.update(1, 1, n);
        }
        if (s == "sum") {
            scanf("%lld%lld",&qL,&qR);
            _sum = 0; _max = -INF; _min = INF;
            tree.query(1, 1, n);
            printf("%lld\n", _sum);
        }
        if (s == "max") {
            scanf("%lld%lld",&qL,&qR);
            _sum = 0; _max = -INF; _min = INF;
            tree.query(1, 1, n);
            printf("%lld\n", _max);
        }
        if (s == "min") {
            scanf("%lld%lld",&qL,&qR);
            _sum = 0; _max = -INF; _min = INF;
            tree.query(1, 1, n);
            printf("%lld\n", _min);
        }
    }

    return 0;
}

/*

10 6
3 9 2 8 1 7 5 0 4 6
add 4 9 4
set 2 6 2
add 3 8 2
sum 2 10
max 1 7
min 3 6

*/