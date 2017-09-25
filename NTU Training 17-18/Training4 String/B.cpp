#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;
typedef long long llint;

const int MAXN = 10010;
const int HASH1 = 3137;
const int HASH2 = 10007;
const int MOD = 1000000007;

map<pii, int> FIND;
int n, powh1[MAXN], powh2[MAXN];
char s[20011][MAXN];

void Clear() {
    FIND.clear();
}

void solve() {
  
    scanf("%d",&n);
    int flag = 0;
    
    for (int j = 1; j <= n; ++j) {
        
        scanf("%s",s[j]);

        int m = strlen(s[j]);
        int h_front1 = 0;
        int h_front2 = 0;
    
        for (int i = 0; i < m; ++i) {
            // h_back1 = ((llint)h_back1 * HASH1 + int(s[m - 1 - i])) % MOD;
            h_front1 = (h_front1 + (llint)powh1[i] * int(s[j][i])) % MOD;

            // h_back2 = ((llint)h_back2 * HASH2 + int(s[m - 1 - i])) % MOD;
            h_front2 = (h_front2 + (llint)powh2[i] * int(s[j][i])) % MOD;
      
            
        }
        FIND[make_pair(h_front1, h_front2)] = j;
        // printf("h1 == %d h2 == %d\n",h_front1, h_front2);
    }

    for (int j = 1; j <= n; ++j) {

        int m = strlen(s[j]);
        int h_front1 = 0;
        int h_front2 = 0;
    
        for (int i = 0; i < m; ++i) {
            h_front1 = (h_front1 + (llint)powh1[i] * int(s[j][i])) % MOD;
            h_front2 = (h_front2 + (llint)powh2[i] * int(s[j][i])) % MOD;
            
            int tmp = FIND[make_pair(h_front1, h_front2)];
            if (tmp && tmp != j) {
                // printf("i %d j %d : yes\n", i,j);
                // printf("h1 == %d h2 == %d\n",h_front1, h_front2);
                flag = 1;
            }
            
        }
    }

    if (!flag) puts("YES");
    else puts("NO"); 
}

int main() {
    
    powh1[0] = powh2[0] = 1;
    for (int i = 1; i < 100; ++i) {
        powh1[i] = (llint)powh1[i - 1] * HASH1 % MOD;
        powh2[i] = (llint)powh2[i - 1] * HASH2 % MOD;
    }

    int TC;
    scanf("%d", &TC);
    while (TC--) {
        Clear();
        solve();
    }
  
    return 0;
}

