#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef long long ll;

const int N = 105;

const ll M = 1e9+7;

typedef struct matrix{
	int n,m;
	ll va[N][N];
	int init(int sn,int sm){
		n = sn;
		m = sm;
		memset(va,0,sizeof(va));
	}
}matrix;

ll multiply(ll x,ll y){
	ll ans = 0;
	while(y){
		if (y & 1) (ans += x) %= M;
		x = (x + x) % M;
		y >>= 1;
	}
	return ans;
}

ll putmatrix(matrix A){
	for (int i = 1;i <= A.n;i++){
		for (int j = 1;j <= A.m;j++)
			printf("%d ",A.va[i][j]);
        cout << endl;
	}
}

matrix mul(matrix a,matrix b){
	matrix c;
	c.init(a.n,b.m);
	for (int i = 1;i <= a.n;i++)
		for (int j = 1;j <= b.m;j++)
			for (int k = 1;k <= a.m;k++)
				(c.va[i][j] += a.va[i][k] * b.va[k][j]) %= M;
	return c;
}


matrix formi(int len){
	matrix c;
	c.init(len,len);
	for (int i = 1;i <= len;i++)
		c.va[i][i] = 1;
	return c;
}

matrix power(matrix a,ll b){
	if (b <= 0) return formi(a.n);
	if (b == 1) return a;
	matrix tmp = power(a,b >> 1);
	tmp = mul(tmp,tmp);
	if (b & 1) tmp = mul(tmp,a);
	return tmp;
}

matrix get(ll m,ll k){
	matrix a;
	a.init(m + 1,m + 1);
	for (int i = 1;i <= m + 1;i++)
	 a.va[1][i] = (k - 1) * k;
	for (int i = 1;i <= m;i++)
	 a.va[i+1][i] = k;
 	return a;
}

ll getf(ll a,ll b,ll n){
	matrix A; 
	A.va[1][1] = 1;
	A.va[1][2] = 1;
	A.va[2][1] = 1;
	A.va[2][2] = 0;
	A.n = 2;
	A.m = 2;
	B.va[1][1] = b;
	B.va[2][1] = a;
	B.n = 2;
	B.m = 1;
	if (n <= 2){  
		if (n == 1) return a;
		if (n == 2) return b;
	}
	A = power(A,n - 2);  
	A = mul(A,B);
	return A.va[1][1];
}

ll calc(ll a,ll b,ll n){  
	if (n < 4) return 0;
	if (n == 4) return 1;
	int pos = (n - 1) / 4;
	pos++;
	ll ans1 = getf(0,1,2 * pos - 2);
	ll ans2 = getf(0,1,2 * pos - 1);
	ll ans3 = getf(0,1,2 * pos);
	if (n % 4 == 1) return ans2;
	if (n % 4 == 2) return (ans1 + ans2 - 1 + M) % M;
	if (n % 4 == 3) return (2 * ans2 + ans1 - 1 + M) % M;
	return ans3;
}

int main(){
	int T;
	ll n,a,b;
	while(cin >> a >> b >> n){   
		ll ans = getf(a,b,n);
		ans = (ans - calc(a,b,n) + M) % M;
		cout << ans << endl;
	}
}

