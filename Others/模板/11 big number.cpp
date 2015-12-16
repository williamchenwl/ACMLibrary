#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
const int N=210000;
typedef struct big{int c[100],len;}big;
big f[51]; int n,k;  big tmp;
big mult(big a,big b)
   { big c=tmp;   
     for (int i=1;i<=a.len;i++)  
      for (int j=1;j<=b.len;j++)
        {c.c[i+j-1]+=a.c[i]*b.c[j];
         c.c[i+j]+=c.c[i+j-1]/10000;
         c.c[i+j-1]%=10000;}
     c.len=a.len+b.len-1;
     if (c.c[a.len+b.len]) c.len=c.len+1;
     return c;  
     }   
big plus(big a,big b)
  {  big s;  
    if (a.len>b.len) s=a,a=b,b=s;
    for (int i=1;i<=a.len;i++)
     { b.c[i]+=a.c[i]; 
       b.c[i+1]+=b.c[i]/10000;
       b.c[i]%=10000;}
      if (b.c[b.len+1]) b.len+1;
     return b;   
    }
      
big pplus(big a,big b)
   { big s;
     for (int i=1;i<=b.len;i++)  
        { if (a.c[i]<b.c[i]) a.c[i]+=10000,a.c[i+1]--;
          a.c[i]-=b.c[i]; 
          }
     for (int i=a.len;i>=0;i--) 
     if (a.c[i]) {a.len=i;break;}
     return a;    
     }
     
int calc(int x)
  { big tmp; tmp.c[1]=3,tmp.len=1;
    for (int i=3;i<=x;i++)  
    f[i]=pplus(mult(f[i-1],tmp),f[i-2]);}  

int print(big a)
   { printf("%d",a.c[a.len]);   
     for (int i=a.len-1;i;i--) 
      { int tmp=a.c[i];
        while (tmp<1000) printf("0"),tmp*=10;
        printf("%d",a.c[i]);} 
     printf("\n");   
      }     
int main()
  {  scanf("%d",&n);  f[1].c[1]=1,f[1].len=1;      
     if (n%2==1) f[2].c[1]=4,f[2].len=1;  
     else f[2].c[1]=3,f[2].len=1;       
     k=n/2; if (n%2==1) k++; 
     calc(k);   big a; a.c[1]=5,a.len=1;   
     if (n%2==1)  print(mult(f[k],f[k]));
     else print(mult(mult(f[k],f[k]),a));
    }
?
