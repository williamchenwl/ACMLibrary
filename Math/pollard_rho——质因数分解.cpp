/*
    correctly used times = 
    used in = { 
   	
    }
*/
/*************************************************************************
	> File Name: pollard_rho——质因数分解.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 14时08分51秒
 ************************************************************************/

long long Pollard_rho(long long x,long long c)
{
        long long i=1,k=2;
        long long x0=rand()%x;
        long long y=x0;
        while(1)
    {
                i++;
                x0=(mult_mod(x0,x0,x)+c)%x;
                long long d=gcd(y-x0,x);
                if(d!=1&&d!=x) return d;
                if(y==x0) return x;
                if(i==k){y=x0;k+=k;}
            
    }

}
void findfac(long long n)
{
        if(Miller_Rabin(n))
    {
                factor[tol++]=n;
                return;
            
    }
        long long p=n;
        while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
        findfac(p);
        findfac(n/p);

}
