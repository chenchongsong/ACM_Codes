#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
int main()
{
	multiset<int> myset;
	multiset<int>:: iterator iter;
	int Lines, Option, num;
	scanf("%d", &Lines);
	while (Lines--)
	{
		scanf("%d %d", &Option, &num);
		if (Option == 1) myset.insert(num);
		if (Option == 2)
		{
			iter = myset.find(num);
			myset.erase(iter);
		}
		if (Option == 3)
		{
			iter = myset.lower_bound(num);
			int Tmp = lower_bound(myset.begin(), myset.end(), num) - myset.begin();
			printf("%d\n", Tmp);
		}
		if (Option == 4)
			printf("%d\n", myset[1]);
		if (Option == 5)
			printf("%d\n", *--myset.lower_bound(num));
		if (Option == 6)
			printf("%d\n", *myset.upper_bound(num));



	}
	return 0;
}