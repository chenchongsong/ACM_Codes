#include<iostream>
using namespace std;
int xb,yb,xh,yh,i,j;
int px[8]={1,2,2,1,-1,-2,-2,-1};
int py[8]={2,1,-1,-2,-2,-1,1,2}; 
int f[21][21]={}; 
bool b[21][21]={};
int main(){
    cin>>xb,yb,xh,yh;
    xb++;yb++;xh++;yh++;
    b[xh][yh]=true;
    for(i=1;i<=8;i++){
       b[xh+px[i]][yh+px[i]]=true;
    }
      f[0][0]=1;
    for (i=1;i<=xb;i++)
      for (j=1;i<=yh;j++)
         if (b[i][j]==false)
            f[i][j]=f[i-1][j]+f[i][j-1];
        cout<<f[xb][yb];
    return 0; 
}
     
