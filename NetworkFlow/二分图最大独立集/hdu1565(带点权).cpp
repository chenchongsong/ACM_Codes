#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <queue>  
using namespace std;  
#define N 400  
#define INF 99999999  
struct Edge  
{  
    int v,next,cap;  
} edge[N*N];  
int cnt,head[N],d[N];  
int ma[25][25];  
int dir[4][2]= {-1,0,1,0,0,-1,0,1};  
void init()  
{  
    memset(head,-1,sizeof(head));  
    cnt=0;  
}  
void addedge(int u,int v,int cap)  
{  
    edge[cnt].v=v,edge[cnt].cap=cap;  
    edge[cnt].next=head[u],head[u]=cnt++;  
    edge[cnt].v=u,edge[cnt].cap=0;  
    edge[cnt].next=head[v],head[v]=cnt++;  
}  
int bfs(int s,int t)  
{  
    memset(d,-1,sizeof(d));  
    d[s]=0;  
    queue<int>q;  
    q.push(s);  
    while(!q.empty())  
    {  
        int u=q.front();  
        q.pop();  
        for(int i=head[u];i!=-1;i=edge[i].next)  
        {  
            int v=edge[i].v,cap=edge[i].cap;  
            if(d[v]==-1&&cap>0)  
            {  
                d[v]=d[u]+1;  
                q.push(v);  
            }  
        }  
    }  
    return d[t]!=-1;  
}  
int dfs(int s,int t,int f)  
{  
    if(s==t||f==0) return f;  
    int flow=0;  
    for(int i=head[s];i!=-1;i=edge[i].next)  
    {  
        int v=edge[i].v,cap=edge[i].cap;  
        if(d[v]==d[s]+1&&cap>0)  
        {  
            int x=min(f-flow,cap);  
            x=dfs(v,t,x);  
            flow+=x;  
            edge[i].cap-=x;  
            edge[i^1].cap+=x;  
        }  
    }  
    if(!flow) d[s]=-2;  
    return flow;  
}  
int Dinic(int s,int t)  
{  
    int flow=0,f;  
    while(bfs(s,t))  
    {  
        while( (f = dfs(s,t,INF)) != 0)  
            flow+=f;  
    }  
    return flow;  
}  
int main()
{  
    int n;  
    while(scanf("%d",&n)!=EOF)  
    {  
        init();  
        int sum=0;  
        for(int i=1; i<=n; i++)  
            for(int j=1; j<=n; j++)  
                {  
                    scanf("%d",&ma[i][j]);  
                    sum+=ma[i][j];  
                } 
        int s=0,t=n*n+1;  
        for(int i=1; i<=n; i++)  
            for(int j=1; j<=n; j++)  
            {  
                if((i+j)%2==0)  
                {  
                    for(int k=0; k<4; k++)  
                    {  
                        int x=i+dir[k][0],y=j+dir[k][1];  
                        if(x<1||x>n||y<1||y>n) continue;  
                        addedge((i-1)*n+j,(x-1)*n+y,INF);  
                    }  
                    addedge(s,(i-1)*n+j,ma[i][j]);  
                }  
                else addedge((i-1)*n+j,t,ma[i][j]);  
            }  
        int ans=Dinic(s,t);  
        printf("%d\n",sum-ans);  
    }  
    return 0;  
}  