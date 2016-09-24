typedef long long dtype;

inline lowbit(int x){ 
	return x & (-x);
}

typedef struct 2DBIT{ 

	dtype c[N][N];

	int n;

	int init(int nx,int mx){ 
		n = max(nx,mx);
	}

	dtype sum(int x,int y){  
		dtype ans = 0;
		for (int i = x;i;i -= lowbit(i))
			for(int j = y;j;j -= lowbit(j))
				ans += c[i][j];
		return ans;
	}

	void add(int x,int y,int val){ 
		if (!x || !y) return 0;
		for (int i = x;i <= n;i += lowbit(i))
			for (int j = y;j <= n;j += lowbit(j))
				c[i][j] += val;
	}

}2DBit;

2DBit C;
