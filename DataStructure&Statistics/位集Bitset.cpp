//位集Bitset.cpp
#include <bitset>

using namespace std;

const int N = 200010;

bitset<N>a;

int example(){ 
	a = a ^ a;
	a ^= (a << x);
	a[0] = 1;
	a[1] = 0;
}


