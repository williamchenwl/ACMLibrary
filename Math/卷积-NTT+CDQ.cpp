#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 41000;

ll x1[N],x2[N];

ll f[N],g[N],n,m;

const ll M = 152076289;

const ll G = 106;

ll powx(ll a,ll b){
	ll ans = 1;
	while(b){
		if (b&1) ans = ans * a % M;
		a = a * a % M;
		b >>= 1;
	}
	return ans;
}

void change(ll *y,int len){
	int i,j,k;
	for(i = 1,j = len / 2;i < len - 1;i++){
		if (i < j) swap(y[i],y[j]);
		k = len / 2;
		while(j >= k){
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}


void ntt (ll *y, int len, int on) {
    change (y, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1) {
        id++;
        ll wn = powx(G, (M - 1) / (1<<id));
        for(int j = 0; j < len; j += h) {
            ll w = 1;
            for(int k = j; k < j + h / 2; k++) {
                ll u = y[k] % M;
                ll t = w * (y[k + h / 2] % M) % M;
                y[k] = (u + t) % M;
                y[k + h / 2] = ((u - t) % M + M) % M;
                w = w * wn % M;
            }
        }
    }
    if (on == -1) {
        for (int i = 1; i < len / 2; i++)
            swap (y[i], y[len - i]);
        ll inv = powx(len, M - 2);
        for(int i = 0; i < len; i++)
            y[i] = y[i] % M * inv % M;
    }
}

ll rev[N],fac[N];

void calcrev(){
	rev[0] = fac[0] = 1;
	for (int i = 1;i < N;i++){
		fac[i] = fac[i - 1] * i % M;
	}
	rev[N - 1] = powx(fac[N-1],M-2);
	for (int i = N - 2;i >= 0;i--)
        rev[i] = rev[i + 1] * (i + 1) % M;
}


void cdq(int l,int r){
	if (l == r){
		f[l] += g[l];
		f[l] %= M;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l,mid);
	int len = 1;
	while(len <= r - l + 1) len <<= 1;
	for (int i = 0;i < len;i++)
		x1[i] = x2[i] = 0;
	for (int i = l;i <= mid;i++)
		x1[i-l] = f[i] * rev[i-1] % M;
	for (int i = 1;i <= r - l;i++)
		x2[i-1] = g[i] * rev[i] % M;

	ntt(x1,len,1); ntt(x2,len,1);
	for (int i = 0;i < len;i++){
		x1[i] = x1[i] * x2[i] % M;
	}
	ntt(x1,len,-1);
	for (int i = mid + 1;i <= r;i++){
		f[i] -= ((x1[i-l-1] * fac[i-1]) % M);
		f[i] += M;
		f[i] %= M;
	}
	cdq(mid+1,r);
}

int main(){
	calcrev(); int T; int nc = 0;
    scanf("%d",&T);
	while(T--){
		ll n,m;
        scanf("%lld%lld",&n,&m);
        memset(f,0,sizeof(f));
		for (int i = 1;i <= n;i++){
			g[i] = powx((m + 1),i * (i - 1) / 2) % M;
		}
        cdq(1,n);
		ll ans = f[n] % M;
		ans = ans - (powx(n,n-2) * powx(m,n-1) % M);
		ans %= M;
		ans += M;
		ans %= M;
		printf("Case #%d: ",++nc);
		printf("%lld\n",ans % M);
	}
	return 0;
}




