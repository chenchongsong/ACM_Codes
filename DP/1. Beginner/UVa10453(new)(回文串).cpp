#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

char str[1005];
int f[1005][1005],opt[1005][1005];

int dfs(int x,int y)
{
    if(x>y)
        return 0;
    if(x==y)
        printf("%c",str[x]);
    else if(opt[x][y]==0)
    {
        printf("%c",str[x]);
        dfs(x+1,y-1);
        printf("%c",str[y]);
    }
    else if(opt[x][y]==1)
    {
        printf("%c",str[y]);
        dfs(x,y-1);
        printf("%c",str[y]);
    }
    else if(opt[x][y]==2)
    {
        printf("%c",str[x]);
        dfs(x+1,y);
        printf("%c",str[x]);
    }
    return 0;
}

int main()
{    
    int n;
    int i,j,k;
    while(scanf("%s",str)!=EOF)
    {
        memset(f,0,sizeof(f));
        memset(opt,0,sizeof(opt));

        n=strlen(str);
        for(i=n-1;i>=0;i--)
        {
            for(j=i+1;j<n;j++)
            {
                if(str[i]==str[j])
                {
                    f[i][j]=f[i+1][j-1];
                }
                else
                {
                    if(f[i+1][j]>f[i][j-1])
                    {
                        f[i][j]=f[i][j-1]+1;
                        opt[i][j]=1;
                    }
                    else
                    {
                        f[i][j]=f[i+1][j]+1;
                        opt[i][j]=2;
                    }
                }
            }
        }

        printf("%d ",f[0][n-1]);
        dfs(0,n-1);
        printf("\n");
    }
    return 0;
}