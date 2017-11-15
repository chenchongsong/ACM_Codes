int C[maxn], B[maxn], dp[maxn];//C是辅助阵列
int LIS(int n){//n表示作LIS的数据范围
    int mmin, mmax, ret=0;
    memset(C, 0x3f, sizeof(C));//inf=0x3f3f3f3f
    for(int i=1; i<=n; i++){//阵列从1开始
        mmin=1, mmax=i;
        while(mmin<mmax){//二分
            int mid=(mmin+mmax)/2;
            if(C[mid]<B[i]) mmin=mid+1;
            else mmax=mid;
        }
        dp[i]=mmin;
        C[mmin]=B[i];
        ret=max(ret, dp[i]);//更新答案
    }
    return ret;
}