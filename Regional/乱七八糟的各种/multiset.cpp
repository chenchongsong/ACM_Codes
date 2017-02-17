#include <set>
#include <cstdio>
using namespace std;
//差别在与set中不允许有重复元素，multiset中允许有重复元素。
void print_set(std::multiset<int> A)
{
	for (std::multiset <int>::iterator it=A.begin();it!=A.end();++it)
    printf("%d ", *it);
	puts("");
}


int main()
{

using namespace std;
multiset<int> myset;
myset.clear();
printf("%d\n", myset.empty());
for (int i=10; i; i--) myset.insert(i*10);
// 10 20 30 40 50 60 70 80 90
multiset<int>::iterator itlow, itup, it;
itlow=myset.lower_bound (30);
itup=myset.upper_bound (60);
myset.erase(itlow,itup);// 10 20 70 80 90
printf("size == %d\n", (int)myset.size());
myset.erase(10);
//20 70 80 90
it = myset.find(70);

printf("count == %d\n", (int)myset.count(80));
//返回容器中元素等于key的元素的个数

return 0;



}