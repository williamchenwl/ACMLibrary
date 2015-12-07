#include<cstdio>
#include<iostream>
using namespace std;
int n,m,sz;
int root[500010],ls[10000010],rs[10000010],sum[10000010];

inline int read()
{
    char ch=getchar();
    while(!(ch>='0'&&ch<='9'))ch=getchar();
    int x=0;
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x;
}

void update(int l,int r,int x,int &y,int v)
{
    y=++sz;
    sum[y]=sum[x]+1;
    if(l==r)return;
    ls[y]=ls[x];rs[y]=rs[x];
    int mid=(l+r)>>1;
    if(v<=mid)update(l,mid,ls[x],ls[y],v);
    else update(mid+1,r,rs[x],rs[y],v);
}

int que(int L,int R)
{
    int l=1,r=n,mid,x,y,tmp=(R-L+1)>>1;
    x=root[L-1];y=root[R];
    while(l!=r)
    {
        if(sum[y]-sum[x]<=tmp)return 0;
        mid=(l+r)>>1;
        if(sum[ls[y]]-sum[ls[x]]>tmp)
        {r=mid;x=ls[x];y=ls[y];}
        else if(sum[rs[y]]-sum[rs[x]]>tmp)
        {l=mid+1;x=rs[x];y=rs[y];}
        else return 0;
    }
    return l;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        int x;x=read();
        update(1,n,root[i-1],root[i],x);
    }
    for(int i=1;i<=m;i++)
    {
        int l,r;l=read();r=read();
        printf("%d\n",que(l,r));
    }
    return 0;
}