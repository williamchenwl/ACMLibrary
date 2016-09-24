#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

long long m,n,p;

long long  pow(long long  a,long long  b,long long  mod)
{
        long long  ans=1;
        while(b)
    {
                if(b&1)
        {
                        b--;
                        ans=(ans*a)%mod;
                    
        }
                else
        {
                        b/=2;
                        a=(a*a)%mod;
                    
        }
            
    }
        return ans;

}
long long  fun1(long long  n,long long  m)
{
        if(n<m)
            return 0;
       long long  ans=1;
        for(int i=1;i<=m;i++)
    {
                ans=ans*(((n-m+i)%p)*pow(i,p-2,p)%p)%p;
            
    }
        return ans;

}
long long  lucas(long long  n,long long  m)
{
        if(m==0)
            return 1;
        return (lucas(n/p,m/p)*fun1(n%p,m%p))%p;

}
int main()
{
     p=10007;
    while(scanf("%lld%lld",&n,&m)!=EOF)
    {
    
      printf("%lld\n",lucas(n,m));    //C(N,M) 
    }
        return 0;

}
