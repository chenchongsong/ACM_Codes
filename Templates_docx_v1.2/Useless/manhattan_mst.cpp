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
            if(ans!=-1) // dist函数计算的是曼哈顿距离
                addedge(p[i].id,p[ans].id,dist(i,ans));
            update(pos,p[i].x+p[i].y,i);
        }
    }
}