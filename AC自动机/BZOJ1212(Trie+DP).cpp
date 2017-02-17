#include <cstdio>
#include <cstring>
#define MaxLen 1000100
using namespace std;
int N, M, size = 0;
char str[MaxLen];
int ch[1000][26];
bool f[MaxLen]; // 表示1~str[i]的前缀 是否能被理解
bool isend[1010];

inline void insert(char* word) {
    int len = strlen(word), j = 0;
    for (int i=0; i<len; ++i) {
        int c = word[i] - 'a';
        if(!ch[j][c]) ch[j][c] = ++size;
        j = ch[j][c];
    }
    isend[j] = 1;
}

inline void Solve(char* text) {
	memset(f, 0, sizeof(f));
	int len = strlen(text);

	f[0] = 1;
	for (int i=0;i<=len;i++)
	{
		if (!f[i]) continue;
		int pos_text = i, pos_word = 0, next_letter = text[pos_text+1]-'a';
		while (ch[pos_word][next_letter] > 0)
		{
			pos_word = ch[pos_word][next_letter];
			pos_text++;
			next_letter = text[pos_text+1]-'a';
			if (isend[pos_word])
				f[pos_text] = 1;
		}
	}
	int Ans = 0;
	for (int i=0;i<len;i++)
		if (f[i])
			Ans = i;
	printf("%d\n",Ans);
}

int main()
{
	scanf("%d%d", &N, &M);
	for (int i=1;i<=N;i++)
	{
		scanf("%s", str);
		insert(str);
	}
	for (int i=1;i<=M;i++)
	{
		scanf("%s", str+1);
		Solve(str);
	}
}