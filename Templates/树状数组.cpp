#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 500010;

int n;
int num[MAXN];
int treeNum[MAXN];

int lowbit(int x){ return x&(-x);}
int getSum(int x)
{
    int sum = 0;
    while(x)
    {sum += treeNum[x];
    x -= lowbit(x); }
    return sum; // V[1]~V[x]
}

void add(int x , int val){
//单点修改(V[x]+=val)
    while(x < MAXN)
    {treeNum[x] += val;
    x += lowbit(x); }
}

int main()
{
    printf("%d\n",getSum(100));
    add(1,100);
    add(2,50);
    add(2,1);
    printf("%d %d %d\n",getSum(1), getSum(2), getSum(3));
    return 0;
}