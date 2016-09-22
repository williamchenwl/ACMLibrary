int T,n,q;
int bin[20],Log[100005];
int a[100005],f[100005][17];
void pre()
{
    for(int i=1;i<=n;i++)f[i][0]=a[i];
    for(int i=1;i<=16;i++)
        for(int x=1;x<=n;x++)
            if(x+bin[i]-1<=n)
                f[x][i]=min(f[x][i-1],f[x+bin[i-1]][i-1]);
            else break;
}
int query(int l,int r)
{
    int t=Log[r-l+1];
    return min(f[l][t],f[r-bin[t]+1][t]);
}
int find(int l,int val)
{
    int L=l,R=n,ans=n+1;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(query(L,mid)>val)L=mid+1;
        else ans=mid,R=mid-1;
    }
    return ans;
}
int main()
{
    bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1; 
    T=read();
    while(T--)
    {
        n=read();
        Log[0]=-1;for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
        for(int i=1;i<=n;i++)
            a[i]=read();
        pre();
        q=read();
        for(int i=1;i<=q;i++)
        {
            int l=read(),r=read();
            int tmp=a[l],now=l;
            while(1)
            {
                now=find(now+1,tmp);
                if(now>r)break;
                tmp=tmp%a[now];
            }
            printf("%d\n",tmp);
        }
    }
    return 0;
}