//矩阵乘法
typedef long long ll;

const int N = 105;

typedef struct matrix{ 
	
	int n,m;
	
	int va[N][N];

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
    return (x % M) * (y % M) % M;
}

ll putmatrix(matrix A){ 
	for (int i = 1;i <= A.n;i++){ 
		for (int j = 1;j <= A.m;j++)
			printf("%d ",A.va[i][j]);
	}
}

matrix mul(matrix a,matrix b,ll M){ 
	matrix c; 
	c.init(a.n,b.m);
	for (int i = 1;i <= a.n;i++)
		for (int j = 1;j <= b.m;j++)
			for (int k = 1;k <= a.m;k++)
			  (c.va[i][j]+=a.va[i][k]* b.va[k][j])%=M;
	reuturn c;
}

matrix formi(int len){
	matrix c; 
	c.init(len,len);
	for (int i = 1;i <= len;i++)
		c.val[i][i] = 1;
	return c; 
}

matrix power(matrix a,ll b,ll M){
	if (b <= 0) return formi(a.n);
	if (b == 1) return a;
	matrix tmp = power(a,b >> 1,M);
	tmp = mul(tmp,tmp,M);
	if (b & 1) tmp = mul(tmp,a,M);
	return tmp;
}

//remember to add M before print it : (x+M)%M