/*
    correctly used times = 
    used in = { 
   	
    }
*/
    
/*************************************************************************
	> File Name: Miller_Rabin——判断素数.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 14时05分12秒
 ************************************************************************/
bool Miller_Rabin(LL n)
{
        int T=S;
        if(n==1||n==0)
            return 0;
        if(n==2)
            return 1;
        if(!(n&1))
            return 0;
        LL x=n-1;
        LL y,s=0,r,a;
        while((x&1)==0)
    {
                s++;
                x>>=1;
            
    }
        r=x;
        while(T--)
    {
                a=rand()%(n-1)+1;
                y=pow_mod(a,r,n);
                if(y!=1&&y!=n-1)
        {
                        for(LL j=1;j<=s-1&&y!=n-1;j++)
            {
                                y=mult_mod(y,y,n);
                                if(y==1)
                                    return 0;
                            
            }
                        if(y!=n-1)
                            return 0;
                    
        }
                else
                    return 1;
            
    }
        return 1;


}
