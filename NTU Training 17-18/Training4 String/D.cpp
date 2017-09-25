# include <stdio.h>
# include <algorithm>
# include <string.h>
# include <queue>
// # include <bits/stdc++.h>
using namespace std;

const int MaxNode = 4000010;
const int Sigma_Size = 26;
int ch[MaxNode][Sigma_Size];
int size=0;
int val[MaxNode];
char str[10000];
 
inline void insert(char* word) {
    int len = strlen(word), j = 0;
    for (int i=0; i<len; ++i) {
        int c = word[i] - 'a';
        if(!ch[j][c]) ch[j][c] = ++size;
        j = ch[j][c];
        val[j] ++;
    }
    printf("%d\n", val[j]-1);
}

int N, ans, T;
 
int main() {
        memset(ch, 0, sizeof(ch));
        memset(val, 0, sizeof(val));
        size = ans = 0;
        
        scanf("%d", &N);
        for (int i=1; i<=N; ++i) {
            scanf("%s", str);
            insert(str);
        }

    return 0;
}