for (j = i;j;j = (j - 1) & i);
//枚举i的子集
int __builtin_popcount(unsigned int x);
//求1的个数
int __builtin_clz(unsigned int x);
//求前缀0的个数
int __builtin_ctz(unsigned int x);
//求后缀0的个数