const int N = 10;

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
		for (int j = 1;j <= b.m;j++){
			for (int k = 1;k <= a.m;k++)
				c.va[i][j] += a.va[i][k] * b.va[k][j] % M;
			c.va[i][j] %= M;
		}
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
	matrix ans; ans = formi(a.n);
    while(b){
        if (b & 1) ans = mul(ans,a);
        a = mul(a,a);
        b >>= 1;
    }
    return ans;
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

int main(){
	int T;
	ll n,a,b;
	while(cin >> a >> b >> n){
		ll ans = getf(a,b,n);
		ans = (ans - calc(a,b,n) + M) % M;
		cout << ans << endl;
	}
}

