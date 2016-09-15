//trie + xor
//卡时卡得丧心病狂啊！！！
//hdu 5536

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 2000 * 32;

int son[N][2];

int cnt[N];

typedef long long ll;

int tot = 0;

int init(int n){
    for (int i = 0;i <= n * 36;i++)
        son[i][1] = son[i][0] = 0;
	for (int i = 1;i <= n * 36;i++)
        cnt[i] = 0;
	tot = 0;
}

void ins(ll x){
	int now = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		cnt[now]++;
		if (!son[now][t]) son[now][t] = ++tot;
		now = son[now][t];
	}
	cnt[now]++;
}

void del(ll x){
	int now = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		cnt[now]--;
		now = son[now][t];
	}
	cnt[now]--;
}

ll walk(ll x){
	int now = 0;;
	ll ans = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		t = t ^ 1;
		if (son[now][t] && cnt[son[now][t]]){
			ans += 1ll << i;
			now = son[now][t];
		}else now = son[now][t ^ 1];
	}
	return ans;
}

ll a[N];

int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for (int i = 1;i <= n;i++)
			scanf("%lld",a + i);
        init(n);
		for (int i = 1;i <= n;i++) ins(a[i]);
		ll ans = 0;
		for (int i = 1;i <= n;i++)
        for (int j = i + 1;j <= n;j++){
            //del(a[i]);
            //del(a[j]);
            ans = max(ans,walk(a[i] + a[j]));
            ins(a[i]);
            ins(a[j]);
        }
		cout << ans << endl;
	}
}
