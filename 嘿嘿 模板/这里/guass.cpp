#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
  
#define MaxN 20
#define eps 1e-6
  
using namespace std;
  
int N;
  
double xs[MaxN][MaxN],mat[MaxN][MaxN],Answer[MaxN];
  
double sqr(double a){
    return a*a;
}
  
void Init(){
    cin >> N;
    for(int i=1;i<=N+1;++i)
        for(int j=1;j<=N;++j)
            cin >> mat[i][j];
    /*for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j){
            mat[i][j]=2.00*(xs[1][j]-xs[i+1][j]);
            mat[i][N+1]+=sqr(xs[1][j])-sqr(xs[i+1][j]);
        }*/
}
  
void Solve(){
    for(int i=0;i<N;++i){
        int to=i;
        for(int j=i+1;j<N;++j)
            if(fabs(mat[j][i])>fabs(mat[to][i])+eps)
                to=j;
        for(int j=i;j<N+1;++j)
            swap(mat[i][j],mat[to][j]);
        for(int j=i+1;j<N;++j){
            double invv=mat[j][i]/mat[i][i];
            for(int k=i;k<N+1;++k)
                mat[j][k]-=invv*mat[i][k];
        }
    }
    for(int i=N-1;i>=0;--i){
        for(int j=i+1;j<=N;++j)
            mat[i][N+1]-=Answer[j]*mat[i][j];
        Answer[i]=mat[i][N+1]/mat[i][i];
    }
}
  
void Print(){
    for(int i=0;i<N;++i){
        printf("%.3lf",Answer[i]);
        if(i<N)
            printf(" ");
    }
    puts("");
}
  
int main(){
    Init();
    Solve();
    Print();
    while (1);
    return 0;
}
