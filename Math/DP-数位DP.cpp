#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll n,m,l,r;

ll dp[30][5][5][5];


ll dpit(ll x){
	ll ans = 0;
	memset(dp,0,sizeof(dp));
	dp[0][0][0][0] = 1;
	dp[0][1][0][0] = 1;
	for (ll i = 1;i <= 19;i++){
		ll bit = x % 10;
		x /= 10;
		ll cnt = 0;
		for (ll v = 9;v >= 0;v--){

			ll odd = v % 2;

			ll t = (v > bit);

			for (ll k = 0;k < 2;k++)
			dp[i][odd][k][t] += dp[i - 1][odd][k^1][t];

			if (i-1)
			dp[i][odd][1][t] += dp[i - 1][odd^1][odd][t];

			if (t == 1){
				for (ll k = 0;k < 2;k++){
				dp[i][odd][k][t] += dp[i - 1][odd][k^1][t^1];
				}
				if (i-1)dp[i][odd][1][t] += dp[i - 1][odd^1][odd][t^1];
			}

            if (t == 0 && v != bit){
                for (ll k = 0;k < 2;k++){
				dp[i][odd][k][t] += dp[i - 1][odd][k^1][t^1];
				}
				if (i-1)dp[i][odd][1][t] += dp[i - 1][odd^1][odd][t^1];
            }

			if (v == bit){
               for (ll k = 0;k < 2;k++){
				dp[i][odd][k][t^1] += dp[i - 1][odd][k^1][t^1];
               }
				if (i-1)dp[i][odd][1][t^1] += dp[i - 1][odd^1][odd][t^1];
			}
			if (v != 0){
				ll t = 0;
				cnt = dp[i][odd][odd^1][t] + dp[i][odd^1][odd][t];
				if (x) cnt += dp[i][odd][odd^1][t^1] + dp[i][odd^1][odd][t^1];
			}
		}
		ans += cnt;
        //if (!x) break;
	}
	return ans;
}

int main(){
	ll T; cin >> T;
	ll nc = 0;
	while(T--){
		ll n,m;
		scanf("%lld%lld",&n,&m);
		if (n > m) swap(n,m);
		ll ans1 = dpit(n - 1);
		ll ans2 = dpit(m);
		printf("Case #%lld: %lld\n",++nc,ans2 - ans1);
	}
}
