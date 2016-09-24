#include <cstdio>
#include <iostream>
#include <cstring>
  
using namespace std;
  
typedef long long ll;
  
const ll M = 1000000007;
  
const int N = 4000008;
  
ll frac[N],inv[N];
  
ll comb(ll n,ll k){
    ll ans = (frac[n] * inv[n - k]) % M;
    return (ans * inv[k]) % M;
}
  
ll powx(ll x,ll y){
    ll ans = 1;
    while(y){
        if (y & 1) ans = (ans * x) % M;
        x = (x * x) % M;
        y >>= 1;
    }
    return ans;
}
  
ll Calc(){
    frac[0] = 1;
    for (int i = 1;i <= 4000005;i++)
        frac[i] = (frac[i - 1] * i) % M;
    inv[0] = 1;
    for (int i = 1;i <= 4000005;i++)
        inv[i] = (inv[i - 1] * powx(i,M-2)) % M;
}
  
int main(){
    Calc();
    ll n,m,k;
    while(cin >> n >> m >> k){
        ll sig = 1; ll ans = 0;
        for (int i = 0;i <= n;i++){
            ll tmpm = m - i * (k + 1);
            if (tmpm < 0) break;
            ans = (ans + ((sig * comb(tmpm + n - 1,n - 1) % M) * comb(n,i) % M)) % M;
            sig *= -1;
        }
        cout << (ans + M) %M << endl;
    }
}