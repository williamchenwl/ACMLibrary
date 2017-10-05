#include <bits/stdc++.h>

#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;

typedef long long  LL;

const int inf=0x3f3f3f3f;

const int N=1e6+10;

int prime[N];//存储素数
int sprime[N];//存储P-1的素因子
bitset<N>pri;//结果只有0和1，判断是否为素数
int k;//记录N以内的素数个数
int cnt;//记录素因子的个数

void is_prime(){
    pri.set();//将所有的二进制数都标为1
    for(int i=2; i<N; i++) {
        if(pri[i]) {
            prime[k++]=i;
            for(int j=i+i; j<N; j+=i)
                pri[j]=0;
        }
    }
}

void Divide(int n)//将n分解为素因子
{
    cnt=0;
    int t=(int)sqrt(1.0*n);
    for(int i=0; prime[i]<=t; i++) {
        if(n%prime[i]==0) {
            sprime[cnt++]=prime[i];
            while(n%prime[i]==0)//因为有可能有多个peime[i]
                n/=prime[i];
        }
    }
    if(n>1)
        sprime[cnt++]=n;//可能只有自己一个素因子
}

LL modexp(LL a,LL b,int mod)//快速幂取余
{
    LL res=1;
    while(b>0) {
        a=a%mod;
        if(b&1)
            res=res*a%mod;
        b=b>>1;
        a=a*a%mod;
    }
    return res;
}

int main()
{
    int p;
    is_prime();
    while(~scanf("%d",&p)) {
        Divide(p-1);
        for(int g=2; g<p; g++) {
            int flag=1;
            for(int i=0; i<cnt; i++) {
                int t=(p-1)/sprime[i];
                if(modexp(g,t,p)==1) {
                    flag=0;
                    break;
                }
            }
            if(flag) {
                int root=g;
                printf("%d\n",root);
                break;//去掉break的话是求所有的原根，加上break是求最小的原根、
            }
        }
    }
    return 0;
}