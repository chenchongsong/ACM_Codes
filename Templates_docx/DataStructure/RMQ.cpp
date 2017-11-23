// d[i][j]: 从i位开始 长度为2^j的一段元素
// 讲所有min直接改为max也可以直接用
void RMQ_init(const vector<int>& A) {
    for(int i = 0; i < A.size(); i++) 
        d_max[i][0] = A[i];
    for (int j=1; (1<<j) <= n; j++)
    for (int i=0; i+(1<<j)-1 < n; i++)
        d_max[i][j] = max(d_max[i][j-1],d_max[i+(1<<(j-1))][j-1]);
}
int RMQ_Min(int L, int R) {  
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return min(d_min[L][k], d_min[R-(1<<k)+1][k]);
}