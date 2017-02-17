/**************************************************************
    Problem: 3172
    User: ccs1997
    Language: C++
    Result: Accepted
    Time:648 ms
    Memory:222728 kb
****************************************************************/
 
# include <stdio.h>
# include <algorithm>
# include <string.h>
# include <queue>
# include <vector>
// # include <bits/stdc++.h>
  
using namespace std;
  
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int M = 1600010;
const int N = 27;
int ch[M][N], fail[M], lst[M], cnt[M], sz=0;
int isend[M];
char str[M];
char t[M];
vector<int> v[M];
int ans[M];
  
inline void insert(int j) {
    int len = strlen(t), p=0;
    for (int i=0; i<len; ++i) {
        int c = t[i] - 'a';
        if(!ch[p][c]) ch[p][c] = ++sz;
        p = ch[p][c];
    }
    isend[p] ++;
    v[p].push_back(j);
}
  
queue<int> q;
inline void getfail() {
    while(!q.empty()) q.pop();
    fail[0] = 0;
    for (int c=0; c<26; ++c) {
        int p = ch[0][c];
        if(p) {
            fail[p] = lst[p] = 0;
            q.push(p);
        }
    }
    while(!q.empty()) {
        int top = q.front(); q.pop();
        for (int c=0; c<26; ++c) {
            int p = ch[top][c];
            if(!p) {
                ch[top][c] = ch[fail[top]][c];
                continue;
            }
            q.push(p);
            int v = fail[top];
            while(v && !ch[v][c]) v = fail[v];
            fail[p] = ch[v][c];
            lst[p] = isend[fail[p]] ? fail[p] : lst[fail[p]];
        }
    }
}
  
inline void tadd(int x) {for (; x; x=lst[x]) cnt[x] ++;}
  
inline void find() {
    int p=0, len = strlen(str);
    memset(cnt, 0, sizeof(cnt));
    for (int i=0; i<len; ++i) {
        int c = str[i] - 'a';
        while(p && !ch[p][c]) p = fail[p];
        p = ch[p][c];
        if(isend[p]) tadd(p);
        else if(lst[p]) tadd(lst[p]);
    }
}
  
int n, T;
  
int main() {
    sz = 0;
    scanf("%d", &n);
    int cur = 0;
    for (int i=1; i<=n; ++i) {
        scanf("%s", t);
        insert(i);
        for (int j=0, jto=strlen(t); j<jto; ++j)
            str[cur++]=t[j];
        str[cur++]='a'+26;
    }
    getfail();
    find();
    for (int i=1; i<=sz; ++i) 
        if(isend[i]) {
            for (int j=0, jto=v[i].size(); j<jto; ++j)
                ans[v[i][j]] = cnt[i];
        }
    for (int i=1; i<=n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}