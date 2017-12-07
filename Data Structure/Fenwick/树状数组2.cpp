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
        scanf("%d", &val);
        int x = i;
        edit(x, val);
        edit(x+1, -val);
    }

    // for (int i=1; i<=n; i++) {
    //     printf("a[%d] == %d\n",i,query(i));
    // }

    for(i=1;i<=m;i++)
    {
        scanf("%d",&t);
        if(t==1)//单点修改
        {
            int x, y, k;
            scanf("%d%d%d", &x, &y, &k);
            edit(x, k);
            edit(y+1, -k);
        }
        if(t==2)//区间查询[]
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", query(x));
        }
    }
    return 0;
}