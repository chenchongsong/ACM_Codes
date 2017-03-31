/*
直接算好像比较困难，所以考虑先算不可读的串的个数，再拿总串数去减。
不可读的串的数量就是在AC自动机上走M步而不经过结尾节点（包括结尾点和fail指向结尾点的节点）的路径条数。
这个怎么求呢？
设f[i][j]表示走i步，现在在j号节点的路径条数。
那么f[i][j]可以转移f[i+1][son[j][k]]。
就是i+1个字符为k的状态。
最后把所有f[m][i]累和就是不可读的串
*/

# include <stdio.h>
# include <algorithm>
# include <string.h>
# include <queue>
// # include <bits/stdc++.h>
using namespace std;

const int MaxNode = 6010, Sigma_Size = 26;
const int mod = 1e4+7;
const int MaxM = 110;
int ch[MaxNode][Sigma_Size], fail[MaxNode];
//int last[MaxNode], cnt[MaxNode];
int size=0;
//int val[MaxNode];
char str[MaxNode*2];

int N, M, Ans, tot_Ans;
int F[MaxM][MaxNode];
bool isDanger[MaxNode];

inline void insert(char* word, int value) {
    int len = strlen(word), j = 0;
    for (int i=0; i<len; ++i) {
        int c = word[i] - 'A';
        if(!ch[j][c]) ch[j][c] = ++size;
        j = ch[j][c];
    }
    isDanger[j] = 1;// 该节点不可以走
}
 
inline void GetFail() {
    queue<int> q;
    fail[0] = 0;
    for (int c = 0; c < Sigma_Size; ++c) {
        int p = ch[0][c];
        if (p) {
            fail[p] = 0;
            q.push(p);
        }
    }
    while(!q.empty()) {
        int father = q.front();
        q.pop();
        isDanger[father] |= isDanger[fail[father]];
            //因为fail路径如果会经过某一单词节点
            //那么那么该单词一定是root-->u这一段的后缀
            //说明单词一定出现过 所以点u也不能走
        for (int c = 0; c < Sigma_Size; ++c) {
            int son = ch[father][c];
            if (son)
            {
                fail[son] = ch[fail[father]][c];
                q.push(son);
            }
            else ch[father][c] = ch[fail[father]][c];
            
        }
        
    }
}
 
inline void DP() {
    int j = 0;
    F[0][0] = 1;

    for (int i=1; i<=M; ++i) {
        for (int j=0; j<=size; j++) {
        	if (isDanger[j]) continue; //j是单词节点
        	for (int c=0; c<Sigma_Size; c++)
        	{
        		int son = ch[j][c];
        		F[i][son] = (F[i][son] + F[i-1][j]) % mod;
        	}
        }
    }

    for (int j=0;j<=size;j++)
        if (!isDanger[j])
    	   Ans = ( Ans + F[M][j]) % mod;

    tot_Ans = 1;
	for (int i=1; i<=M; i++)
    	tot_Ans = (tot_Ans * 26) % mod;
    Ans = ((tot_Ans - Ans) % mod + mod) % mod;
}
 
int main() {
    scanf("%d%d", &N, &M);
    memset(ch, 0, sizeof(ch));
    memset(fail, 0, sizeof(fail));
    memset(F, 0, sizeof(F));
    size = Ans = 0;
    for (int i=1; i<=N; ++i) {
        scanf("%s", str);
        insert(str, 1);
    }
    GetFail();
    DP();
    printf("%d\n", Ans);
    return 0;
}

/*
3 3
ABC
BC
C
*/