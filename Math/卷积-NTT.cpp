const LL MOD = 998244353;
const LL g = 3;
LL Pow(LL a, LL n)
{
    LL ret = 1;
    while(n)
    {
        if(n & 1) ret = ret * a % MOD;
        n >>= 1;
        a = a * a % MOD;
    }
    return ret;
}
void rader(LL y[], int len)
{
    for(int i = 1, j = len / 2; i < len - 1; i++)
    {
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
void ntt(LL y[], int len, int on)
{
    rader(y, len);
    for(int h = 2; h <= len; h <<= 1)
    {
        LL wn = Pow(g, (MOD-1)/h);
        if(on == -1) wn = Pow(wn, MOD-2);
        for(int j = 0; j < len; j += h)
        {
            LL w = 1;
            for(int k = j; k < j + h / 2; k++)
             {
                LL u = y[k];
                LL t = w * y[k + h / 2] % MOD;
                y[k] = (u + t) % MOD;
                y[k+h/2] = (u - t + MOD) % MOD;
                w = w * wn % MOD;
            }
        }
    }
    if(on == -1)
     {
        LL t = Pow(len, MOD - 2);
        for(int i = 0; i < len; i++)  y[i] = y[i] * t % MOD;
     }
}

int A[100005],n;
LL x1[1000005], fac[100005], inv[100005], x2[1000005];

bool cmp(int a,int b)
{
     return a>b;
}

void prepare()
{
    fac[0]=inv[0]=1;
    for(int i=1;i<=100000;i++) fac[i]=fac[i-1]*i%MOD;
    inv[100000]=Pow(fac[100000],MOD-2);
    for(int i=100000-1;i>0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

void work()
{
      int len=1;
      x1[n]=0;
      for(int i=1;i<=n;i++) x1[n-i]=fac[i-1]*A[i]%MOD * Pow(2,n-i) %MOD;
      x2[0]=1;
      for(int i=1;i<=n;i++) x2[i]=inv[i];

      while(len<=n+n) len<<=1;
      for(int i=n+1;i
      ntt(x1,len,1);
      ntt(x2,len,1);
      for(int i=0;i
      ntt(x1,len,-1);
      for(int i=0;i
}

int main()
{
    //freopen("out.txt","w",stdout);
         int T=0;
         scanf("%d",&T);
         prepare();


         while(T--)
         {
               scanf("%d",&n);
               for(int i=1;i<=n;i++) scanf("%d",&A[i]);
               sort(A+1,A+n+1,cmp);
               work();
               LL ans=0;
               for(int i=n-1;i>=0;i--)
               {
                      ans=(ans+x1[i])%MOD;
                      printf("%lld ",ans);
               }
               printf("\n");
         }
}