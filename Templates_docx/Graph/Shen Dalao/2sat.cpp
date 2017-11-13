#include <cstdio>
#include <vector>
using namespace std;
#define MAXN 1000
int n,cnt=0,sol[MAXN];
vector<int>G[MAXN*2];
bool mark[MAXN*2];

//x=xval or y = yval
void add_constrain(int x,int xval,int y,int yval)
{
    //x is xval OR y is yval
    x=2*x+xval;
    y=2*y+yval;
    G[x^1].push_back(y); //!x->y
    G[y^1].push_back(x); //!y->x
}

bool dfs(int u)
{
    if(mark[u^1]) return false;
    if(mark[u]) return true;
    mark[u] = true;
    sol[cnt++]=u;
    for(int i = 0;i<G[u].size();i++)
    {
        if(!dfs(G[u][i])) return false;
    }
    return true;
}

bool twosat()
{
    for(int i=0;i<2*n;i+=2)
    {
        if(!mark[i] && !mark[i^1])//未涂色
        {
            cnt=0;
            if(!dfs(i))// i result in contradiction
            {
                cnt=0;
                while(cnt) mark[sol[--cnt]]=0;
                //i的结果全部不要
                if(!dfs(i^1)) return false; //alawys contradic
            }
        }
    }
    return true;
}