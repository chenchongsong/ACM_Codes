#include<cstdio>
using namespace std;
int n,m;


int bit[600005];
int lowbit(int u){return u&(-u);}//最后一位1在的地方
void edit(int u,int v)  //a[u]的值增加v
{
    for(int j=u;j<=n;j+=lowbit(j))
        bit[j]+=v;
}
int query(int p) //区间和 a[1]+...+a[n]
{
    int ans=0,i;
    for(i=p;i>0;i-=lowbit(i))
        ans+=bit[i];
    return ans;
}
// a[1~n]


int main()
{
    int i,t,val,a,b;
    scanf("%d%d", &n, &m);

    for(i=1;i<=n;i++)
    {
        scanf("%d",&val);
        edit(i,val);
    }

    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&t,&a,&b);
        if(t==1)//单点修改
            edit(a, b);
        if(t==2)//区间查询[]
            printf("%d\n", query(b)-query(a-1));
    }
    return 0;
}