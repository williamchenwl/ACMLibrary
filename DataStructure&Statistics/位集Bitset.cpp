/*
    some operations can be expressed as the
    "or xor and >> <<" operations for some binary number
    take care of the memory problem
*/

#include <bitset>

using namespace std;

const int N = 200010;

bitset<N>a;

int example(){
	a = a ^ a;
	a ^= (a << x);
	a[0] = 1;
	a[1] = 0;
	a.set(1) // set the position 1 to 1
	a.reset() //clear to 0
}

int __builtin_popcount(unsigned int x);

int __builtin_clz(unsigned int x);
//求前缀0的个数

int __builtin_ctz(unsigned int x);
//求后缀0的个数




