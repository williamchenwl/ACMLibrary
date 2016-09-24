double ans;
bitset<1005>edge[maxn];

void floyd()
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(edge[j][i]) edge[j]|=edge[i];
        }
    }
    int num;
    ans=0;
    for(i=1;i<=n;i++)
    {
        num=0;
        for(j=1;j<=n;j++)
        {
            if(edge[j][i]) num++;
        }
        ans+=1.0/num;
    }
}