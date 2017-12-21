#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#define ll long long
using namespace std;

int r, c, m;
int op, x1, qL, x2, qR, v;
int _sum, _min, _max;

const int maxnode = 1<<17;

ll MIN(ll a, ll b) {return a < b ? a : b;}
ll MAX(ll a, ll b) {return a > b ? a : b;}

struct IntervalTree{
ll addv[maxnode*4],setv[maxnode*4];
ll sumv[maxnode*4],minv[maxnode*4];
ll maxv[maxnode*4];

void maintain(ll o, ll L, ll R){
        ll lc = o*2, rc = o*2+1;
        sumv[o] = maxv[o] = minv[o] = 0;
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
    void query(ll o, ll L, ll R, ll add){
//只需要set时可以删去第四个参数
        if(setv[o] >= 0){ // when set included
            ll v = setv[o] + addv[o] + add;
            _sum += v * (MIN(R, qR)-MAX(L, qL)+1);
            _max = MAX(_max, v);
            _min = MIN(_min, v);
        }
        else if(qL <= L && qR >= R){
//当前区间完全包含于询问中
            _sum += sumv[o] + add*(R-L+1);
            _max = MAX(_max, maxv[o]+add);
            _min = MIN(_min, minv[o]+add);
        }
        else{ // 递归统计 累加参数add
            ll lc = o*2, rc = o*2+1;
            ll M = L + (R-L)/2;
            if(qL <= M) query(lc, L, M, add+addv[o]);
            if(qR > M) query(rc, M+1, R, add+addv[o]);
        }
    } 
} tree[25];

const int INF = 0x3f3f3f3f;

int main(){
    while(scanf("%d%d%d",&r,&c,&m) != EOF){

        memset(tree, 0, sizeof(tree));
        for(int i = 0; i <= r; i++){
            memset(tree[i].setv, -1, sizeof(tree[i].setv));
            // tree[i].setv[1] = 0;/// wrong answer point
        }
        while(m--){
            scanf("%d%d%d%d%d",&op,&x1,&qL,&x2,&qR);
            if(op < 3){
                scanf("%d",&v);
                for(int x = x1; x <= x2; x++){
                    tree[x].update(1, 1, c);
                }
            }
            else{
                _max = -INF;_min = INF;_sum = 0;
                for(int x = x1; x <= x2; x++){
                    tree[x].query(1, 1, c, 0);
                }
                printf("%d %d %d\n",_sum, _min, _max);
            }
        }
    }

    return 0;
}

/*

4 4 8
1 1 2 4 4 5
3 2 1 4 4
1 1 1 3 4 2
3 1 2 4 4
3 1 1 3 4
2 2 1 4 4 2
3 1 2 4 4
1 1 1 4 3 3

*/