/*************************************************************************
	> File Name: 反素数.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 17时13分49秒
 ************************************************************************/

/*
* 网上模板：
* 对于任何一个正整数x，其约数为g(x)，对于任意i<x,都有g(i)<g(x),则x为反素数
* */
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

typedef long long lld;

lld prime[20]={2,3,5,7,11,13,17,19,23,29,31,37,39,41,43,47,53};
lld n;
lld bestcurr,largecnt;/*bestcurr 相同最大因数个数中值最小的数，largecnt：n范围内最大的因数个数*/
void getarcprime(lld curr,int cnt,int limit,int k)
{
        if(curr>n)
            return ;
        if(largecnt<cnt)/*此时枚举到的因数个数比之前记录的最大的因数个数要大，就替换最大因数个数*/
    {
                largecnt=cnt;
                bestcurr=curr;
            
    }
        if(largecnt==cnt && bestcurr>curr)/*替换最优值*/
            bestcurr=curr;
        lld temp=curr;
        for(int i=1;i<=limit;i++)
    {
                temp=temp*prime[k];
                if(temp>n)
                    return;
                getarcprime(temp,cnt*(i+1),i,k+1);

            
    }

}
int main()
{
        int i,cas;
        scanf("%d",&cas);
        for(i=1;i<=cas;i++)
    {
                scanf("%lld",&n);
                bestcurr=0;
                largecnt=0;
                getarcprime(1,1,50,0);
                printf("Case #%d: %lld\n",i,bestcurr);
            
    }
        return 0;

}
