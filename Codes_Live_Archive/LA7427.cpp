#include<cstdio>
#include<cstring>
#define maxn 100010
#define maxm 100010
using namespace std;
long long N,x,y,tot,ans;
long long head[maxn],next[maxm],v[maxm],link[maxn];
long long Cnt,R[maxn];
bool vis[maxn];
long long Ans1[maxn],Ans2[maxn],Ans3[maxn];
 
 
void Clear()
{
    Cnt=0;
    ans=0;
    tot=0;
    memset(head,0,sizeof(head));
    memset(next,0,sizeof(next));
    memset(v,0,sizeof(v));
    memset(link,0,sizeof(link));
    memset(R,0,sizeof(R));
    memset(Ans1,0,sizeof(Ans1));
    memset(Ans2,0,sizeof(Ans2));
    memset(Ans3,0,sizeof(Ans3));
}
 
 
void add(long long a,long long b)
{
    v[++tot]=b;next[tot]=head[a];head[a]=tot;
}
 
void Cal(long long left,long long a,long long b,long long val)
{
    for (long long i=1;i<=Cnt;i++)
    {
        if (R[i]==val)
        {
            add(left,i);//printf("from %lld ---- to %lld\n",left,i);
            return;
        }
    }
    R[++Cnt]=val;
    add(left,Cnt);//printf("from %lld ---- to %lld\n",left,Cnt);
}
 
int dfs(long long now)
{
    for (int i=head[now];i;i=next[i])
        if (!vis[v[i]])
        {
            vis[v[i]]=1;
            if (!link[v[i]] || dfs(link[v[i]]))
            {
                link[v[i]]=now;
                return 1;
            }
        }
    return 0;
}
 
int main()
{
    while(scanf("%lld",&N)!=EOF)
    {
        Clear();
        //scanf("%lld",&N);
        for (int i=1;i<=N;i++)
        {
            scanf("%lld%lld",&x,&y);
            Ans1[i]=x;
            Ans2[i]=y;
            Cal(i,x,y,x+y);
            Cal(i,x,y,x-y);
            Cal(i,x,y,x*y);
        }
        for (long long i=1;i<=N;i++)
        {
            memset(vis,0,sizeof(vis));
            if (dfs(i)) ans++;
        }
        //printf("%lld\n",ans);
        if (ans!=N) {printf("impossible\n");}
        else
        {
            for (long long i=1;i<=Cnt;i++)
            {
                if (link[i])
                {
                    Ans3[link[i]]=R[i];
                    //printf("%lld--------%lld\n",link[i],i);
                }
            }
            for (long long i=1;i<=N;i++)
            {
                printf("%lld ",Ans1[i]);
                if (Ans1[i]+Ans2[i]==Ans3[i])
                    printf("+");
                else
                {
                    if (Ans1[i]-Ans2[i]==Ans3[i])
                        printf("-");
                    else
                    {
                        if (Ans1[i]*Ans2[i]==Ans3[i])
                            printf("*");
                    }
                }
                 
                printf(" %lld = %lld\n",Ans2[i],Ans3[i]);
            }
        }
             
    }
    //while (1);
    return 0;
}