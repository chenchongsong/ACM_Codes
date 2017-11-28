// discovery:
// sg[0] = 0
// sg[4k+1] = 4k+1
// sg[4k+2] = 4k+2
// sg[4k+3] = 4k+4
// sg[4k+4] = 4k+3

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
const int N=1000010;

int sg[N];

int g(int x){
    bool mex[1010];
    memset(mex,0,sizeof(mex));
    if(sg[x]!=-1)
        return sg[x];
    
    for(int i=x-1;i>=0;i--)
        mex[g(i)]=1;
    
    for(int i=1;i<=x/2;i++){
        // split into two piles:
        // x and i-x
        int ans=0;
        ans^=g(i);
        ans^=g(x-i);
        mex[ans]=1;
    }
    
    for(int i=0;;i++)
        if(!mex[i])
            return sg[x]=i;
}

int main(){

    memset(sg,-1,sizeof(sg));
   
    for(int i=0;i<=100;i++)
        printf("sg[%d] == %d\n",i,sg[i] = g(i));

    int x;
    for(int i=0;i<20;i++){
        scanf("%d",&x);
        g(x);
        printf("sg[%d]=%d\n",x,sg[x]);
    }
    return 0;
}