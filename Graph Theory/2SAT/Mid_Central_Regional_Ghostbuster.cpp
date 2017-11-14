#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
#define MAXN 4005
#define INF 0x3f3f3f3f
typedef pair<int,bool> node;
//T表示行 F表示列
map<node, int> mmap;
vector<int>v[8005];
int x[MAXN], y[MAXN], visited[MAXN];


int n, dfs_clock=0, scc_cnt=0;
int pre[MAXN*2],low[MAXN*2];
int sccno[MAXN*2];
stack<int> S;
vector<int> G[MAXN*2];
void Clear() {
    for (int i = 0; i < n*2; i++)
        G[i].clear();
    dfs_clock = scc_cnt = 0;
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(sccno, 0, sizeof(sccno));
}
void add_constrain(int x,int xval,int y,int yval) {
    //x=xval or y = yval
    x=2*x+xval;
    y=2*y+yval;
    G[x^1].push_back(y); //!x->y
    G[y^1].push_back(x); //!y->x
}
void dfs(int u) { // scc
    pre[u] = low[u] = ++dfs_clock;
    S.push(u);
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!pre[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]); 
        }
        else if (!sccno[v]) 
            low[u] = min(low[u],pre[v]);
    }
    if (low[u] == pre[u]) {
        scc_cnt++;
        int tmp = 0;
        do {
            tmp = S.top(); S.pop();
            sccno[tmp] = scc_cnt;
        } while (tmp != u);
    }
} // end of dfs
bool twosat() {
    for (int i=0; i<n*2; i++)
        if (!pre[i])
            dfs(i);
    for (int i=0; i<n; i++)
        if (sccno[i*2] == sccno[i*2+1])
            return false;
    return true;
}

bool checksol(int dis)
{
    int i,j,k,xvec,yvec,p,len;
    for(i=0;i<n;i++)
    {
        yvec = mmap[ make_pair(x[i],true) ];
        xvec = mmap[ make_pair(y[i],false)];

        len = v[xvec].size();
        j=lower_bound(v[xvec].begin(),v[xvec].end(),i)-v[xvec].begin();

        for(;j<len;j++)
        {
            p = v[xvec][j];
            if(p==i) continue;
            if( (abs(x[p]-x[i])-1)/2 < dis) //constrain
                add_constrain(p,1,i,1);
        }

        len = v[yvec].size();
        j=lower_bound(v[yvec].begin(),v[yvec].end(),i)-v[yvec].begin();
        for(;j<len;j++)
        {
            p = v[yvec][j];
            if(p==i ) continue;
            if( (abs(y[p]-y[i])-1)/2 < dis)
                add_constrain(p,0,i,0);
        }
    }
    return twosat();

}

int main() {
    int i,xmin,xmax,mid,cnt=0;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d%d",&x[i],&y[i]);
        if(mmap.find(make_pair(x[i],true)) == mmap.end())
        {
            v[cnt].push_back(i);
            mmap[make_pair(x[i],true)]= cnt++;
        }
        else
        {
            v[ mmap[  make_pair(x[i],true) ] ].push_back(i);
        }

        if(mmap.find(make_pair(y[i],false)) == mmap.end())
        {
            v[cnt].push_back(i);
            mmap[make_pair(y[i],false)]= cnt++;
        }
        else
        {
            v[ mmap[  make_pair(y[i],false) ] ].push_back(i);
        }
    }

    Clear();
    if(checksol(1000001))
    {
        puts("UNLIMITED");
        return 0;
    }
    xmin=0;
    xmax=10000001; // MAN_pos + 1
    while(xmin + 1 < xmax)
    {
        Clear();
        mid=xmin+(xmax-xmin)/2;
        if(checksol(mid)) xmin=mid;
        else xmax=mid;
    }

    printf("%d",xmin);
    return 0;
}