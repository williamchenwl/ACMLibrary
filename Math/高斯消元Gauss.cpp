//高斯消元Gauss.cpp
int swap(int x,int y){
      for (int i=0;i<=n;i++){
        double tmp=c[x][i];
        c[x][i]=c[y][i];
        c[y][i]=tmp;   
       }
 }
  
int guass(){
     for (int i=1;i<=n;i++)
         for (int k=i,j=i;j<=n;j++)
         {if (fabs(c[j][i-1])>fabs(c[k][i-1])) k=j;
         swap(i,k);
         for (int j=i+1;j<=n;j++)
         for (int k=n;k>=i-1;k--)
         c[j][k]-=c[i][k]*c[j][i-1]/c[i][i-1];}
         
}
  
int solve(){
    double ans[N];
    ans[n]=1;
    for (int i=n;i>=1;i--)
      {  double sum=0;
         for (int j=i;j<=n;j++)
         sum-=ans[j]*c[i][j];
         ans[i-1]=sum/c[i][i-1];
         }  
     for (int i=0;i<n;i++)
      if (i) printf(" %.3lf",ans[i]);
      else printf("%.3lf",ans[i]); 
      printf("\n");
}
