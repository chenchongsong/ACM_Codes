#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1010
using namespace std;
int n, k;
int f[maxn][27]; 
//f[i][c] 前i组 第i组以c结尾 的方案数
//f[i][26] = min{ f[i][c] | c=0~25}
bool vis[maxn][26];
int cnt[maxn];
char s[maxn];
void Clear()
{
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	memset(f, 127, sizeof(f));
}

int main()
{
	int Case;
	scanf("%d", &Case);
	while (Case--)
	{
		scanf("%d", &k);
		scanf("%s", s);
		n = strlen(s);
		Clear();

		for (int i=0; i<(n/k); i++)
		{
			for (int j=0; j<k; j++)
			{
				int pos = i*k+j;
				vis[i+1][s[pos]-'a'] = 1;
			}
			for (int c=0; c<26; c++)
				cnt[i+1] += vis[i+1][c];
		}

		for (int c=0; c<26; c++)
			if (vis[1][c])
				f[1][c] = cnt[1];
		for (int i=2;i<=(n/k);i++)
		{
			for (int c=0; c<26; c++)
			{
				if(!vis[i][c]) continue;
				int& ans = f[i][c];
				for (int c0=0; c0<26; c0++)
				{
					if (!vis[i-1][c0]) continue;
					if (c0 == c)
					{
						if (cnt[i]==1) ans=min(ans, f[i-1][c0]);
						else ans = min(ans, f[i-1][c0]+cnt[i]);
						continue;
					}
					if (vis[i][c0])
						ans = min(ans, f[i-1][c0]+cnt[i]-1);
					else
						ans = min(ans, f[i-1][c0]+cnt[i]);
				}
			}
		}
		int ans = (int)1e8;
		for (int c=0; c<26; c++)
			ans = min(ans, f[n/k][c]);
		printf("%d\n", ans);
	}
	return 0;
}