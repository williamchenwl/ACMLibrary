
const int N=300100;
 
ll cnt,y;
 
 
ll euler(ll n){
        ll ret = 1,i;
        for (i = 2;i * i <= n;i++)
            if (n % i == 0){
                n /= i;
                ret *= (i - 1);
                while (n % i == 0){
                    n /= i;
                    ret *= i;
                }
        }
        if (n > 1)
            ret *= (n - 1);
        return ret;
}
 
ll quick(ll a, ll b,ll m)
{
    ll ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=(ans*a)%m;
            b--;
        }
        b/=2;
        a=a*a%m;
    }
    return ans;
}
 
ll cal(ll a,ll b,ll y,ll c)
{
    ll phi,p,ans;
    phi=euler(c);
    p=1;
    for(ll i = 1;i <= y;i++){
        p = p * b;
        if(p > phi) break;
    }
    if(p>phi)
    {
        return quick(a,(quick(b,y,phi) + phi),c);
    }
    else ans=quick(a,p,c);
    return ans;
}
 
int main()
{
    ll a,b,c;
    while(cin>>a>>b>>y>>c)
    {
        ll ans=cal(a,b,y,c);
        cout<<ans<<endl;
    }
}
 