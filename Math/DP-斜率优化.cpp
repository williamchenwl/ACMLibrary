#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN=500010;

int dp[MAXN];
int q[MAXN];//队列
int sum[MAXN];

int head,tail,n,m;
// dp[i]= min{ dp[j]+M+(sum[i]-sum[j])^2 };
int getDP(int i,int j)
{
    return dp[j]+m+(sum[i]-sum[j])*(sum[i]-sum[j]);
}

int getUP(int j,int k) //yj-yk部分
{
    return dp[j]+sum[j]*sum[j]-(dp[k]+sum[k]*sum[k]);
}
int getDOWN(int j,int  k)
{
    return 2*(sum[j]-sum[k]);
}

int main()
{
  //  freopen("in.txt","r",stdin);
  //  freopen("out.txt","w",stdout);
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++)
           scanf("%d",&sum[i]);
        sum[0]=dp[0]=0;
        for(int i=1;i<=n;i++)
           sum[i]+=sum[i-1];
        head=tail=0;
        q[tail++]=0;
        for(int i=1;i<=n;i++)
        {
            //把斜率转成相乘，注意顺序，否则不等号方向会改变的
            while(head+1<tail &&  getUP(q[head+1],q[head])<=sum[i]*getDOWN(q[head+1],q[head]))
               head++;
            dp[i]=getDP(i,q[head]);
            while(head+1<tail && getUP(i,q[tail-1])*getDOWN(q[tail-1],q[tail-2])<=getUP(q[tail-1],q[tail-2])*getDOWN(i,q[tail-1]))
                    tail--;
            q[tail++]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}