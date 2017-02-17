#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#define MOD 10007  
int ch[6005][30],no[6005],f[6005],q[6005],dp[105][6005];  
char s[105];  
int sz=0;  
void tj()  
{  
    int i,u=0,len=strlen(s);  
    for(i=0;i<len;i++)  
    {  
        if(ch[u][s[i]-64]==0) ch[u][s[i]-64]=++sz;  
        u=ch[u][s[i]-64];  
    }  
    no[u]=1;  
}  
void build()  
{  
    int i,head=0,tail=0,u,v;  
    for(i=1;i<=26;i++)  
        if(ch[0][i]>0) q[tail++]=ch[0][i];  
    while(head<tail)  
    {  
        u=q[head++];  
        no[u]|=no[f[u]];  
        for(i=1;i<=26;i++)  
        {  
            v=ch[u][i];  
            if(v>0)  
            {  
                f[v]=ch[f[u]][i];  
                q[tail++]=v;  
            }  
            else ch[u][i]=ch[f[u]][i];  
        }  
    }  
}  
int main()  
{  
    int n,m,i,j,k,ans=0,ans2=1;  
    scanf("%d%d",&n,&m);  
    for(i=1;i<=n;i++)  
    {  
        scanf("%s",s);  
        tj();  
    }  
    build();  

printf("here----%d %d %d %d %d\n", ch[0][0], ch[0][1], ch[0][2], ch[0][3], ch[0][4]);






    dp[0][0]=1;  
    for(i=1;i<=m;i++)  
    {  
        for(j=0;j<=sz;j++)  
            if(no[j]==0&&dp[i-1][j]>0)  
                for(k=1;k<=26;k++)  
                    dp[i][ch[j][k]]=(dp[i][ch[j][k]]+dp[i-1][j])%MOD;  
    }  
    for (int i=1;i<=m;i++)
        for (int node =0;node<=sz;node++)
            printf("%d--%d   : %d\n", i,node, dp[i][node]);




    for(i=0;i<=sz;i++)
    {
        printf("%d===%d\n", i, dp[m][i]);
        if(no[i]==0) ans+=dp[m][i];  
    }



    for(i=1;i<=m;i++)  
        ans2=(ans2*26)%MOD; 

printf(" %d--- %d\n", ans2, ans);


    printf("%d",((ans2-ans)%MOD+MOD)%MOD);  
    return 0;  
}