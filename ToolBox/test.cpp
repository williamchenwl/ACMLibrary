#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>

//非负整数
void scan_(T & ret){
	char c; ret = 0;
	while((c = getchar()) < '0' || c > '9');
	while(c >= '0' && c <= '9') ret = ret * 10 + (c - '0'),c = getchar();
}

typedef long long ll;

ll a[10];

int main(){
    int n = 10;
    for (int i = 0;i < 10;i++)
        scan_(a[i]);
    for (int i = 0;i < 10;i++)
        cout << a[i] << endl;
}

