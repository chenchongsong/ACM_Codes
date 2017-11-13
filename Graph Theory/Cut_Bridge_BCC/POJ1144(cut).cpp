#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
#define MAXN 110
struct Edge{
    int u,v;
};
vector<int>G[MAXN],bcc[MAXN];
vector<Edge>bridge;
int low[MAXN],pre[MAXN],dfs_clock=0,iscut[MAXN],bccno[MAXN],bcc_cnt=0;
//bccno是每个点在哪块 bcc是第i块有哪些点
//点编号0~n-1
stack<Edge>s;//保存在当前bcc中的边, 割顶的bccno无意义, 因为存在于多个bcc中

void dfs(int u, int fa) 
{
    low[u]=pre[u]=++dfs_clock;
    int len=G[u].size(),i,child=0;
    for(i=0;i<len;i++)
    {
        int v=G[u][i];
        Edge e = {u,v};
        if(!pre[v]) //not accessed yet
        {
            
            s.push(e);//store cur edge
            dfs(v,u);
            child++;
            low[u]=min(low[u],low[v]);
            if(low[v] >= pre[u])  //if cut, bcc find
            {
                if(low[v] > pre[u])
                {
                    bridge.push_back(e);
                }
                iscut[u]=1;
                bcc_cnt++;//bcc start from 1
                bcc[bcc_cnt].clear();
                while(1)
                {
                    Edge x = s.top();
                    s.pop();
                    if(bccno[x.u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;
                    }
                    if(bccno[x.v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;
                    }
                    if(x.u==u && x.v==v) break;
                }
            }
        }
        else if( pre[u] > pre[v] && v!=fa ) //early than father
        {
            s.push(e);
            low[u]=min(low[u],pre[v]);
        }

    }
    if(child<=1 && fa<0)
        iscut[u]=0;
}

int n, m;
void Clear() {
    for (int i=1; i<=n; i++)
        G[i].clear(),
        bcc[i].clear();
    bridge.clear();
    while (!s.empty()) s.pop();
    memset(low, 0, sizeof(low));
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock=0, bcc_cnt=0;
}


int main() {
    while (1) {
        int i,a,b;
        char ch;
        scanf("%d",&n);
        if (n == 0) break;

        Clear();
        while (scanf("%d", &a) == 1 && a) {
            while((ch=getchar())!='\n') {
                scanf("%d", &b);
                G[a].push_back(b);
                G[b].push_back(a);
            } 
        }
        for(i=1; i<=n; i++)
            if(!pre[i])
                dfs(i,-1);
        int cnt_cut = 0;
        for (int i=1; i<=n; i++) {
            cnt_cut += iscut[i];
        }
        printf("%d\n", cnt_cut);

    }
    return 0;
}