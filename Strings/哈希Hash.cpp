/*
	BKDR_HASH是一种可动态变换的Hash函数
	可以直接溢出
*/

typedef unsigned long long ull;

ull seed = 137;

int bkdr_hash(){ 
	int len = s.length();
	ull ans = 0;
	for (int i = 1;i < s.length();i++)
		ans = ans * seed + s[i];
}


