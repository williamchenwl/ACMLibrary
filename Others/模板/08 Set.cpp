#include <set>
#include <cstdio>
#include <cmath>
using namespace std;
int n,t,k,a,b,x;
set<int>s;
int main()
  {  scanf("%d",&n); k=(int)sqrt(n);
     for (int i=1;i<=k;i++)
        if (n%i==0)
         {  b=n/i;
            for (x=1;x<=n;x+=b)
            if ((x+1)%i==0) s.insert(x);
            for (x=b-1;x<=n;x+=b)
            if ((x-1)%i==0) s.insert(x);
         }
     if (s.empty()) printf("None");
     while (!s.empty())
     {   printf("%d\n",*s.begin());
         s.erase(s.begin());
     }
    }



#include <cstdio>
#include <set>
using namespace std;
const int inf = ~0U>>2;
typedef set<int>::iterator sit;
set<int>s;
 
int main(){
   int n,a,b,ans=0,type;
   scanf("%d",&n);
   s.insert(inf); s.insert(-inf);
   while (n--)
    {scanf("%d%d",&a,&b); 
     if (s.size()==2)type=a,s.insert(b);
     else if(type==a)s.insert(b);
     else
     {sit i=s.lower_bound(b);
      int r=*i-b,l=b-*(--i);
      if (l<=r)  ans+=l,s.erase(i);
      else ans+=r,s.erase(++i);
      ans%=1000000;}
    }
   printf("%d\n",ans);
  }