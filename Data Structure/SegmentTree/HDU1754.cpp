#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
struct node{
    int L,R,mid,xmax,xmin;
    long long sum,lazy;
}tree[600005];//三倍N
int a[200005],t1,t2,t3;

void build(int l, int r, int u) //u
{
    if (l==r)
    {
        tree[u].R=tree[u].L=tree[u].mid=l;
        tree[u].sum=tree[u].xmax=tree[u].xmin=a[r];
        tree[u].lazy=0;
        return;
    }
    int mid=l+(r-l)/2;
    tree[u].L=l;
    tree[u].R=r;
    tree[u].mid=mid;
    tree[u].lazy=0;
    build(l,mid,u*2);
    build(mid+1,r,u*2+1);
    tree[u].sum=tree[2*u].sum+tree[2*u+1].sum;
    tree[u].xmax=max(tree[2*u].xmax,tree[2*u+1].xmax);
    tree[u].xmin=min(tree[2*u].xmin,tree[2*u+1].xmin);
}

long long i_sum(int l, int r, int u)
{
    if(tree[u].L==l && tree[u].R==r)
        return tree[u].sum+tree[u].lazy*(r-l+1);

    if(tree[u].lazy!=0 && tree[u].R!=tree[u].L)//push down
    {
        tree[2*u].lazy+=tree[u].lazy;
        tree[2*u+1].lazy+=tree[u].lazy;
        tree[u].sum=tree[u].sum+tree[u].lazy*(tree[u].R-tree[u].L+1);
        tree[u].lazy=0;
    }

    if(l>tree[u].mid) //Right son
        return i_sum(l,r,u*2+1);
    else if(r<=tree[u].mid) //Left son
        return i_sum(l,r,u*2);
    else
        return i_sum(l,tree[u].mid,2*u)+i_sum(tree[u].mid+1,r,2*u+1);
}

long long i_max(int l, int r, int u)
{
    if(tree[u].L==l && tree[u].R==r)
        return tree[u].xmax+tree[u].lazy;
    if(tree[u].lazy!=0 && tree[u].R!=tree[u].L)
    {
        tree[2*u].lazy+=tree[u].lazy;
        tree[2*u+1].lazy+=tree[u].lazy;
        tree[u].sum=tree[u].sum+tree[u].lazy*(tree[u].R-tree[u].L+1);
        tree[u].xmax+=tree[u].lazy;
        tree[u].xmin+=tree[u].lazy;
        tree[u].lazy=0;
    }
    if(l>tree[u].mid) //Right son
        return i_max(l,r,u*2+1);
    else if(r<=tree[u].mid) //Left son
        return i_max(l,r,u*2);
    else
        return max(i_max(l,tree[u].mid,2*u),i_max(tree[u].mid+1,r,2*u+1));

}

void edit_interval(int l, int r, int val, int u)
{
    if(tree[u].L==l && tree[u].R==r)
    {
        tree[u].lazy+=val;
        tree[u].xmax+=val;
        return;
    }
    tree[u].sum+=(min(r,t2)-max(t1,l)+1)*val;
    //当前区间内的所有数都+val
    if(l>tree[u].mid) //Right son
        edit_interval(l,r,val,2*u+1);
    else if(r<=tree[u].mid) //Left son
        edit_interval(l,r,val,2*u);
    else
    {
        edit_interval(l,tree[u].mid,val,2*u);
        edit_interval(tree[u].mid+1,r,val,2*u+1);
    }
    tree[u].xmax=max(tree[2*u].xmax,tree[2*u+1].xmax);
}

int main() {
    int n,i,m,choice;
    scanf("%d%d",&n,&m);

    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,n,1);

    for(i=1;i<=m;i++)
    {
        string s;
        cin >> s;

        if (s[0] == 'Q') choice = 3;
        if (s[0] == 'U') choice = 1;
        if(choice == 1)
        {
            scanf("%d%d",&t1,&t3);
            // int tmp = i_max(t1,t1)
            edit_interval(t1,t1,t3,1);
        }
        else if(choice == 2)
        {
            scanf("%d%d",&t1,&t2);
            printf("%lld\n",i_sum(t1,t2,1));
        }
        else{
            scanf("%d%d",&t1,&t2);
            printf("%lld\n",i_max(t1,t2,1));
        }

    }
    return 0;
}