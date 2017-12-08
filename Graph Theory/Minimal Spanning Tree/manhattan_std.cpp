#include <iostream>
#include <cstdio>
#include <algorithm>
#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 1000005;
struct Point{
    int x,y,id;
    bool operator < (const Point p) const{
        return x!=p.x?x<p.x:y<p.y;
    }
}p[maxn];

struct Edge{
    int u, v, w;
    bool operator < (const Edge rhs) const{
        return w< rhs.w;
    }
} e[maxn<<2];
int n, tot, fa[maxn];
int getf(int x){
    return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
int dist(int i,int j){
    return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}
void addedge(int u,int v,int w){
    e[tot].u=u;
    e[tot].v=v;
    e[tot++].w=w;
}

#define INF 0x3f3f3f3f

// ========== BIT ==========
struct BIT {
    int min_val,pos;
    void init()
    {min_val=INF;pos=-1;}
} bit[maxn];
void update(int x,int val,int pos){
    for(int i=x;i>=1;i-=lowbit(i))
        if(val<bit[i].min_val)
            bit[i].min_val=val,bit[i].pos=pos;
}
int ask(int x,int m){
    int min_val=INF, pos=-1;
    for(int i=x;i<=m;i+=lowbit(i))
        if(bit[i].min_val<min_val)
            min_val=bit[i].min_val,pos=bit[i].pos;
    return pos;
}
int Manhattan_minimum_spanning_tree(int n,Point *p){
    int a[maxn],b[maxn]; // tmp
    for(int dir=0;dir<4;dir++){
        //4种坐标变换
        if(dir==1||dir==3){
            for(int i=0;i<n;i++)
                swap(p[i].x,p[i].y);
        }
        else if(dir==2){
            for(int i=0;i<n;i++)
                p[i].x=-p[i].x;
        }
        // 我们将坐标按X排序(Y为第二关键字)，将Y-X离散化
        // 用BIT来维护，查询对于某一个(X0,Y0)
        // 查询比(Y0-X0)大的中X1+Y1最小的点
        sort(p, p + n);
        for(int i=0;i<n;i++){
            a[i]=b[i]=p[i].y-p[i].x;
        }
        sort(b, b + n);
        int m = unique(b,b+n)-b;
        for(int i=1;i<=m;i++)
            bit[i].init(); //对于四种坐标变换 每次新建一个树状数组
        for(int i=n-1;i>=0;i--){ // x从大到小 保证X1>=X0
            int pos=lower_bound(b,b+m,a[i])-b+1; //BIT中从1开始
            int ans=ask(pos,m);
            if(ans!=-1)
                addedge(p[i].id,p[ans].id,dist(i,ans));
            update(pos,p[i].x+p[i].y,i);
        }
    }

    // kruskal
    sort(e,e+tot);
    int cnt=n-1;
    for(int i=0;i<n;i++)
        fa[i]=i;
    long long ans = 0;
    for(int i=0;i<tot;i++){
        int u=e[i].u,v=e[i].v;
        int fu=getf(u), fv=getf(v);
        if(fu!=fv){
            cnt--;
            fa[fu]=fv;
            ans += (long long) e[i].w;
            if(cnt==0)
                return ans;
        }
    }
    return -1;
}
int main(){
    scanf("%d", &n);
    tot=0;
    for(int i=0;i<n;i++){
        scanf("%d%d",&p[i].x,&p[i].y);
        p[i].id=i;
    }
    printf("%d\n",Manhattan_minimum_spanning_tree(n,p));
    return 0;
}