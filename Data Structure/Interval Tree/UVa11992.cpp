#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int r, c, m;
int op, x1, qL, x2, qR, v;
int _sum, _min, _max;

const int maxnode = 1<<17;

struct IntervalTree{
    int addv[maxnode*4],setv[maxnode*4];
    int sumv[maxnode*4],minv[maxnode*4],maxv[maxnode*4];

    void maintain(int o, int L, int R){
        int lc = o*2, rc = o*2+1;
        if(L < R){
            sumv[o] = sumv[lc] + sumv[rc];
            maxv[o] = max(maxv[lc], maxv[rc]);
            minv[o] = min(minv[lc], minv[rc]);
        }
        if(setv[o] >= 0){
            minv[o] = maxv[o] = setv[o];
            sumv[o] = setv[o] * (R-L+1);
        }
        if(addv[o]){
            minv[o] += addv[o];
            maxv[o] += addv[o];
            sumv[o] += addv[o] * (R-L+1);
        }
    }
    void pushdown(int o){
        int lc = o*2, rc = o*2+1;
        if(setv[o] >= 0){
            setv[lc] = setv[rc] = setv[o];
            addv[lc] = addv[rc] = 0;
            setv[o] = -1;
        }
        if(addv[o]){
            addv[lc] += addv[o]; /// wrong answer
            addv[rc] += addv[o]; /// wrong answer
            addv[o] = 0;
        }
    }
    void update(int o, int L, int R){
        int lc = o*2, rc = o*2+1;
        if(qL <= L && qR >= R){
            if(op == 2) { // set
                setv[o] = v;
                addv[o] = 0;
            } // op == 1 : Add
            else{
                addv[o] += v;
            }
        }
        else{
            pushdown(o);
            int M = L + (R-L)/2;
            if(qL <= M) update(lc, L, M);
            else maintain(lc, L, M);
            if(qR > M) update(rc, M+1, R);
            else maintain(rc, M+1, R);
        }
        maintain(o, L, R); /// wrong answer;
    }
    void query(int o, int L, int R, int add){
        if(setv[o] >= 0){
            int v = setv[o] + addv[o] + add;
            _sum += v * (min(R, qR)-max(L, qL)+1); /// wrong answer
            _max = max(_max, v);
            _min = min(_min, v);
        }
        else if(qL <= L && qR >= R){
            _sum += sumv[o] + add*(R-L+1); /// wrong answer
            _max = max(_max, maxv[o]+add); /// wrong answer
            _min = min(_min, minv[o]+add); /// wrong answer
        }
        else{
            int lc = o*2, rc = o*2+1;
            int M = L + (R-L)/2;
            if(qL <= M) query(lc, L, M, add+addv[o]);
            if(qR > M) query(rc, M+1, R, add+addv[o]);
        }
    } 
}tree[25];

const int INF = 0x3f3f3f3f;

int main(){
    while(scanf("%d%d%d",&r,&c,&m) != EOF){

        memset(tree, 0, sizeof(tree));
        for(int i = 0; i <= r; i++){
            memset(tree[i].setv, -1, sizeof(tree[i].setv));
            tree[i].setv[1] = 0;/// wrong answer point
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
