#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 200010;
const int CHARSET_SIZE = 257;
string s, s2;
int sa[maxn], rk[maxn], ht[maxn];

void buildSA(const string& str, int n, int m) {
    static int rk1[maxn], rk2[maxn], tmpSA[maxn], cnt[maxn];

    fill(cnt, cnt + m, 0);
    for (int i = 0; i < n; i++) cnt[(int)s[i]]++;
    for (int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) rk[i] = cnt[(int)s[i]]-1;

    for (int len = 1; len <= n; len <<= 1) {
        for (int i = 0; i < n; i++) rk1[i] = rk[i];
        for (int i = 0; i < n; i++) rk2[i] = (i + len >= n) ? 0 : rk1[i + len];

        fill(cnt, cnt + n, 0);
        for (int i = 0; i < n; i++) cnt[rk2[i]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) tmpSA[--cnt[rk2[i]]] = i;

        fill(cnt, cnt + n, 0);
        for (int i = 0; i < n; i++) cnt[rk1[i]]++;
        for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
        for (int j = n-1, i; j >= 0; j--) i = tmpSA[j], sa[--cnt[rk1[i]]] = i;

        bool unique = true;
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            int cur = sa[i], last = sa[i - 1];

            rk[cur] = rk[last];
            if (rk1[cur] == rk1[last] && rk2[cur] == rk2[last]) unique = false;
            else rk[cur]++;
        }
        if (unique) break;
    }   
}

void getHeight(const string& str, int n) {
    for (int i = 0, k = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (s[i + k] == s[j + k]) k++;
        ht[rk[i]] = k;
    }
}

int main() {
    getline(cin, s);
    getline(cin, s2);
    int len1 = s.size();
    s = s + '$' + s2; 
        
    int N = s.size();
    buildSA(s, N, CHARSET_SIZE);
    getHeight(s, N);

    int ans = 0;
    for(int i = 1; i < N; i++) {
        if((sa[i]<len1) && (sa[i-1]>len1))
            ans = max(ans,ht[i]);
        if((sa[i]>len1) && (sa[i-1]<len1))
            ans = max(ans,ht[i]);
    }
    printf("%d\n", ans);

    return 0;
}