#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 2005
#define N 2005

// ========== templates ==========
#include <cstring>
int n, cnt=0, sol[MAXN*2];
vector<int> G[MAXN*2];
bool mark[MAXN*2];
void Clear() {
    for (int i = 0; i < MAXN*2; i++)
        G[i].clear();
    memset(mark, 0, sizeof(mark));
    cnt = 0;
}
//x=xval or y = yval
void add_constrain(int x,int xval,int y,int yval) {
    //x is xval OR y is yval
    x=2*x+xval;
    y=2*y+yval;
    G[x^1].push_back(y); //!x->y
    G[y^1].push_back(x); //!y->x
}
bool dfs(int u) {
    if(mark[u^1]) return false;
    if(mark[u]) return true;
    mark[u] = true;
    sol[cnt++]=u;
    for(int i = 0;i<G[u].size();i++)
        if(!dfs(G[u][i]))
            return false;
    return true;
}
bool twosat() {
    for(int i=0;i<2*n;i+=2)
        if(!mark[i] && !mark[i+1]) { //未涂色
            cnt=0;
            if(!dfs(i)) { //出现contradiction
                while(cnt) mark[sol[--cnt]]=0; //i的结果全部不要
                if(!dfs(i+1)) return false; //alawys contradic
            }
        }
    return true;
}
// ========== end of templates ==========

int tim[MAXN][2]; //time of early & late arrival 
int ABS(int x) {return x>0?x:-x;}
bool check(int gap) {
    Clear();
    for (int i=0; i<n; i++)
        for (int t1=0; t1<2; t1++)
            for (int j=i+1; j<n; j++)
                for (int t2=0; t2<2; t2++) {
                    if (ABS(tim[i][t1]-tim[j][t2])<gap)
                        add_constrain(i,t1^1,j,t2^1);
                }
    return twosat();
}

int main() {
    while(scanf("%d",&n) != EOF) {
        
        int L = 0,R = 0, mid = 0;
        for (int i = 0; i < n; i++) {
            for(int t = 0; t < 2; t++) {
                scanf("%d", &tim[i][t]);
                R = max(R, tim[i][t]);
            }
        }
        R = R + 1;
        while(L + 1 < R) {
            if (check(mid = (L+R) >> 1)) L = mid;
            else R = mid;
        }
        printf("%d\n",L);
        // for (int i=1; i<=20; i++) {
        //     printf("check(%d) ; %d\n",i,check(i));
        // }
    }
    return 0;
}

/*



10
44 156
153 182
48 109
160 201
55 186
54 207
55 165
17 58
132 160
87 197

*/