#include <cstdio>
#include <cstring>
// #include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 200010;
const int CHARSET_SIZE = 357;
vector<int> s;
char tmps[maxn];
int belong[maxn];
int sa[maxn], rk[maxn], ht[maxn];
int rk1[maxn], rk2[maxn], tmpSA[maxn], cnt[maxn];
int N, num, ansLen;
bool vis[110];

void buildSA(const vector<int>& str, int n, int m) {
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
void getHeight(const vector<int>& str, int n) {
    for (int i = 0, k = 0; i < n; i++) {
        if (rk[i] == 0) continue;
        int j = sa[rk[i] - 1];
        if (k) k--;
        while (s[i + k] == s[j + k]) k++;
        ht[rk[i]] = k;
    }
}

void Clear() {
    s.clear();
    memset(belong, 0, sizeof(belong));
    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    memset(ht, 0, sizeof(ht));
}

void printAns() {
    
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= N; i++) {
        if (ht[i]>=ansLen)
            vis[belong[sa[i]]] = 1,
            vis[belong[sa[i-1]]] = 1;
        else {
            int count_diff_strings = 0;
            for (int i=1; i<=num; i++)
                count_diff_strings += vis[i];

            if (count_diff_strings > num/2) {
                int start = sa[i-1], end = start + ansLen;
                for (int pos = start; pos < end; pos++)
                    printf("%c", (char)(s[pos]-100));
                puts("");
            }
            memset(vis, 0, sizeof(vis));
        }
    }
    puts("");
}

bool Check(int len) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= N; i++) {
        if (ht[i]>=len)
            vis[belong[sa[i]]] = 1,
            vis[belong[sa[i-1]]] = 1;
        else {
            int count_diff_strings = 0;
            for (int i=1; i<=num; i++) {
                count_diff_strings += vis[i];
                // bottle neck of time_complexity
                // O(log(num) * N * num)
            }
            if (count_diff_strings > num/2)
                return true;
            memset(vis, 0, sizeof(vis));
        }
    }
    return false;
}

int binarySearch() {
    int l = 0, r = 2000+1, mid = 0;
    while (l + 1 < r) {
        if (Check(mid = (l+r) >> 1))
            l = mid;
        else
            r = mid;
    }
    return l;
}

int main() {
    int len = 0;
    while (scanf("%d", &num) && num) {

        Clear();
        for (int i=1; i<=num; i++) {
            scanf("%s", tmps);
            len = strlen(tmps);
            for (int j=0; j<len; j++) {
                s.push_back((int)tmps[j] + 100);
                belong[s.size()-1] = i;
            }
            if (i != num) s.push_back(i);
            belong[s.size()-1] = i;

        }
        N = s.size();
        buildSA(s, N, CHARSET_SIZE);
        getHeight(s, N);

        // for (int i=0; i<=N; i++)
        //     printf("sa[%d] = %d\n", i, sa[i]);
        // for (int i=0; i<=N; i++) {
        //     printf("ht[%d] = %d\n", i, ht[i]);
        //     printf("from %d --- to %d:::   %d  %d\n", belong[sa[i]-1], belong[sa[i]],sa[i]-1,sa[i]);
        // }

        ansLen = binarySearch();
        // printf("Ans == %d\n" , ansLen);
        if (!ansLen)
            puts("?\n");
        else printAns();
    }

    return 0;
}