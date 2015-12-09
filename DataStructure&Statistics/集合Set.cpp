//集合
#include <set>

set<int>S;

S.insert();

set<int>::iterator i;

i = S.begin();

while (i != S.end())
	printf("%d\n",*i++);

S.clear();

S.count(4);

S.empty();

S.erase();

S.find();

S.lower_bound();

//大于或等于某值的第一个位置

S.rbegin();

S.upper_bound();

//大于某个数的第一个位置
