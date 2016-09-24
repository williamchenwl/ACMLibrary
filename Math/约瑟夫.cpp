/*
    correctly used times = 
    used in = { 
   	
    }
*/
/*************************************************************************
	> File Name: 约瑟夫.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 14时10分01秒
 ************************************************************************/

LL fun(LL n)
{
        if(n==0)
            return 1;
        LL f=0;
        for(LL i=1;i<=n;i++)
            f=(f+m)%i;
        return f+1;

}

//M=2时

LL fun(LL n)
{
        if(n==1)
            return 1;
        if(n&1)
            return 2*fun((n-1)/2)+1;
        else
            return  2*fun(n/2)-1;

}

//某些约瑟夫可采用线段树来做
