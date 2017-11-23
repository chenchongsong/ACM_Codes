#include <cstdio>  
#include <cmath>  
#include <algorithm>
#include <vector>  
using namespace std;  
const int maxn = 50000+10;  
  
int d_max[maxn][20];
int d_min[maxn][20];
vector<int> a;
int n, q;

// d[i][j]: 从i位开始 长度为2^j的一段元素
void RMQ_init(const vector<int>& A) {
    for(int i = 0; i < A.size(); i++) 
        d_min[i][0] = A[i],
        d_max[i][0] = A[i];
    for (int j=1; (1<<j) <= n; j++)
    for (int i=0; i+(1<<j)-1 < n; i++)
        d_min[i][j] = min(d_min[i][j-1],d_min[i+(1<<(j-1))][j-1]),
        d_max[i][j] = max(d_max[i][j-1],d_max[i+(1<<(j-1))][j-1]);
}
int RMQ_Min(int L, int R) {  
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return min(d_min[L][k], d_min[R-(1<<k)+1][k]);
}
int RMQ_Max(int L, int R) {  
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return max(d_max[L][k], d_max[R-(1<<k)+1][k]);  
}  
  
int main() {  
    while(scanf("%d%d", &n, &q) != EOF) {
        a.clear();
        a.resize(n);
        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        RMQ_init(a);
        while(q--) {
            int a,b;  
            scanf("%d%d", &a, &b);
            a--; b--;
            printf("%d\n", RMQ_Max(a, b) - RMQ_Min(a, b));
        }     
    }
    return 0;
}  