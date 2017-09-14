//ex_gcd
ll ex_gcd(ll a,ll b,ll& x,ll& y){   
	if (!b) return x = 1,y = 0,a;
	ll gcd = ex_gcd(b,a%b,x,y);
	ll t = x; x = y; y = t - a / b * y;
	return gcd;
}

//prime_set
int prim[N],p_tab[N],pcnt;
void get_prim(){   
	for (int i = 2;i < N;i++){  
		if (!prim[i]) p_tab[++pcnt] = i;
		for (int j = 1;j <= pcnt && i * p_tab[j] < N;j++){  
			prim[i * p_tab[j]] = 1;
			if (!(i % p_tab[j])) break;
		}
	}
}

//num_theory_inverse 递推逆元,模数M
int inv[N],sinv[N];
void get_inv(){  
	int i;
	for (inv[0] = inv[1] = 1,i = 2;i < M;i++){   
		inv[i] = -inv[M%i]*(M/i)%M；
		while(inv[i] < 0) inv[i] += M;
 	}

 	for (sinv[0] = 1,i = 1;i < M;i++)
 		sinv[i] = sinv[i - 1] * inv[i] % M;
}

//CRT

ll CRT(ll* a,ll* b,int n){  
	ll ans,P = 1;
	for (int i = 0;i < n;i++)
		P *= a[i];
	for (int i = 0;i < n;i++){
		ll x,y;
		ll now = P / a[i];
		ex_gcd(now,a[i],x,y);
		ans = (ans + now * x * a[i]) % P;
	}
	while(ans < 0) ans += P;
}