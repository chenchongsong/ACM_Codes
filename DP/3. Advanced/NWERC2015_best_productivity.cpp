#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

#define MaxN 210

typedef pair<int, int> pii;

int N, P;
vector<pii> v, rest;
vector<int> lens;

int dp[MaxN][MaxN]; // d[i][j] - i intervals into j groups; i >= j

int main () {
    cin >> N >> P;
    
    v.resize (N);
    for (int i = 0; i < N; ++i) cin >> v[i].first >> v[i].second;
    
    rest.resize (1);
    for (int i = 0; i < N; ++i) {
        bool is_empty = true;
        for (int j = 0; j < N; ++j)
            if (i != j && v[i].first < v[j].first && v[j].second < v[i].second) {
                is_empty = false;
                break;
            }
        
        if (is_empty) 
            rest.push_back (v[i]);

        else// completely covers other interval
            lens.push_back (v[i].second - v[i].first);

    }

    sort (rest.begin() + 1, rest.end()); // first从小到大 second从小到大
    int Z = rest.size();

    memset (dp, 0x80, sizeof (dp)); // -INF
    dp[0][0] = 0;
    
    for (int i = 1; i < Z; ++i)
        for (int j = 1; j <= P; ++j)
            for (int k = i; k >= 1; --k) {
                if (rest[k].second <= rest[i].first) break;
                // when k.l < k.r <= i.l < i.r
                // 两区间没有交集 直接break
                // 因为之后的区间next_k 也不会与i有交集
                // （因为若有交集 next_k.l < k.l && next.r > i.r > k.r)
                // (这种next_k一开始就被扔进lens了)
                
                if (dp[k - 1][j - 1] != -1)
                    dp[i][j] = max(dp[i][j], dp[k - 1][j - 1] +
                                   rest[k].second - rest[i].first);
            }

    sort (lens.begin(), lens.end(), greater<int>()); // 从大到小
    for (int j = 1; j < lens.size(); ++j) lens[j] += lens[j - 1];
    
    int best = max (dp[Z - 1][P], 0);
    
    if (!lens.empty())
        for (int j = 1; j < min(P,(int)lens.size()+1); ++j)
            if (dp[Z - 1][P - j] != -1)
                best = max (best, dp[Z - 1][P - j] + lens[j - 1]);
                // lens里面的前j个工人 每一个工人单独占一个machine
    cout << best << endl;
    
    return 0;
}