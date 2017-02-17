#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=10000000;
int n;
vector<int> tree;
int find(int x)
{
    return lower_bound(tree.begin(),tree.end(),x)-tree.begin()+1;
}
int main()
{
    scanf("%d",&n);
    tree.reserve(200005);
    int opt,x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&opt,&x);
        switch(opt)
        {
            case 1:tree.insert(upper_bound(tree.begin(),tree.end(),x),x);break;
            case 2:tree.erase(lower_bound(tree.begin(),tree.end(),x));break;
            case 3:printf("%d\n",find(x));break;
            case 4:printf("%d\n",tree[x-1]);break;
            case 5:printf("%d\n",*--lower_bound(tree.begin(),tree.end(),x));break;
            case 6:printf("%d\n",*upper_bound(tree.begin(),tree.end(),x));break;
        }
    }
    return 0;
}