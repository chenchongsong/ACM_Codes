#include <queue>  
#include <vector>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <iostream>  
#include <algorithm>  
using namespace std;  
typedef long long ll;  
typedef unsigned long long ull;  
const int inf=0x3f3f3f3f;  
const ll INF=0x3f3f3f3f3f3f3fll;  
const int maxn=230;  
int f[maxn],spouse[maxn],Next[maxn],Q[maxn],mark[maxn],vis[maxn];  
int n,Qtail;  
vector<int>G[maxn];  //存一个邻接表

//一朵花内 对于所有的点x f[x]的值相等
int find1(int x){  
    if(x!=f[x]) f[x]=find1(f[x]);  
    return f[x];  
}  
void unite(int a,int b){  
    int aa=find1(a);  
    int bb=find1(b);  
    if(aa==bb) return ;  
    f[aa]=bb;  
}



int findLCA(int x,int y){  
    static int t=0;  
    t++;  
    while(1)
    {  
        if(x!=-1)
        {  
            x=find1(x);  
            
            if(vis[x]==t) return x;  
            //当前位置x被另外一个人来过 这个地方就是LCA
            
            vis[x]=t;
            
            if(spouse[x]!=-1)  
                x=Next[spouse[x]];
            else
                x=-1;  
        }  
        swap(x,y);  //x与y交替往上爬
    }  
}

//缩点
void goup(int a,int p){  
    while(a!=p){  
        int b=spouse[a],c=Next[b];  // a <--> b --- c
        if(find1(c)!=p) Next[c]=b;  // 因为bc现在在同一朵花内 所以把虚边变成双向的
        if(mark[b]==2) mark[Q[Qtail++]=b]=1;  //  一朵花内所有的点都是等价的 都改成1型点 重新拓展
        if(mark[c]==2) mark[Q[Qtail++]=c]=1;
        unite(a,b);unite(b,c);
        a=c; //往上 （c也是一个1型点）
    }  
}

void findaugment(int s){  
    for(int i=0;i<n;i++) Next[i]=-1, f[i]=i, mark[i]=0, vis[i]=-1;  
    
    Q[0]=s; Qtail=1; mark[s]=1;  
    for(int head=0;spouse[s]==-1&&head<Qtail;head++){  
        int x=Q[head];  //从一个1型点开始拓展
        for(unsigned int i=0;i<G[x].size();i++){  
            int y=G[x][i];  
            if(spouse[x]!=y && find1(x)!=find1(y) && mark[y]!=2)
                //spouse[x] == y  说明往回找了 直接无视
                //在同一朵花内
                //找到了2 直接无视
            {  
                if(mark[y]==1) //找到一个1 缩点
                {  
                    int p=findLCA(x,y);  
                    if(find1(x)!=p) Next[x]=y;  
                    if(find1(y)!=p) Next[y]=x;
                    //只是名义上缩成一个点（花） 实际上最终增广的时候还是要从花的内部走的
                    //所以要添加上虚边 双向的
                    
                    goup(x,p);goup(y,p);   // 从两条链分别往上
                }
                else if(spouse[y]==-1)//找到一个没有配偶的单身汉y 直接增广
                {  
                    Next[y]=x; //虚边
                    for(int j=y;j!=-1;) //直到j==-1 也就是回到s
                    {
                        int k=Next[j];
                        int l=spouse[k];
                        spouse[j]=k; spouse[k]=j; j=l;
                    }  
                    break;
                }
                else//找到一个正常的已经被匹配的节点 拉进队列
                {  
                    Next[y]=x;  // y --- x
                    mark[Q[Qtail++]=spouse[y]]=1;  // 1型点 拉进队列 下次从该1型点开始拓展
                    mark[y]=2;  //2型点 
                    // S(1)(x)---(2)(y)-->(1)spouse[y](x)
                }  
            }  
        }  
    }  
}


int num[maxn][maxn]; // 0 or 1  
int main(){  
    scanf("%d",&n);  
    int x,y;  
    for(int i=0;i<n;i++){  
        for(int j=0;j<n;j++) num[i][j]=0;  
    }  
    while(scanf("%d%d",&x,&y)!=EOF){  
        x--;y--;  
        if(x!=y&&num[x][y]==0){  
            num[x][y]=num[y][x]=1;  
            G[x].push_back(y);  
            G[y].push_back(x);  
        }  
    }  
    for(int i=0;i<n;i++) spouse[i]=-1;  
    for(int i=0;i<n;i++){  
        if(spouse[i]==-1) findaugment(i);  
    }  
    int ans=0;  
    for(int i=0;i<n;i++) if(spouse[i]!=-1) ans++;  
    printf("%d\n",ans);  
    for(int i=0;i<n;i++){  
        if(spouse[i]!=-1&&spouse[i]>i) printf("%d %d\n",i+1,spouse[i]+1);  
    }  
    return 0;  
}