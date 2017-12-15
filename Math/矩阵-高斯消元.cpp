struct GuassX
{
    int equ,var;
    double a[maxNode+20][maxNode+20],x[maxNode+20];
    void init()
    {
        memset(a,0,sizeof(a));
    }
    void build()
    {
       equ=var=tot + 1;

       for(int i = 0;i <= tot;i++)
       {
           a[i][i]=-1;
       }
       a[0][var]=-1;

       for(int i = 0;i <= tot;i++)if(!mark[i])
       {
           for(int j = 0;j < 6;j++)
           {
               int y=son[i][j];
               a[y][i]+=1.0/6;
           }
       }
    }
    int elimination()
    {
        int i,j,k,col,max_r;
        for(k=0,col=0;k<equ&&col<var;k++,col++)
        {
            max_r=k;
            for(i=k+1;i<equ;i++)
            {
                if(fabs(a[i][col] )>fabs(a[max_r][col] ) ) max_r=i;
            }
            if(fabs(a[max_r][col])< 1e-10)  return 0;
            if(k!=max_r)
            {
                for(j=col;j<=var;j++)  swap(a[k][j],a[max_r][j]  );
            }
            for(j=col+1;j<=var;j++)  a[k][j]/=a[k][col];

            a[k][col]=1;

            for(i=0;i<equ;i++) if(i!=k)
            {
                for(j=col+1;j<=var;j++) a[i][j]-=a[k][j]*a[i][col];

                a[i][col]=0;
            }
        }
        for(i=0;i<equ;i++)  x[i]=a[i][var];
        return 1;
    }
}gauss;