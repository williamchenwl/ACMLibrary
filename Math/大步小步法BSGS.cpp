//大步小步法 用于求(Y^X = Z) mod P
#define ll long long
using namespace std;
int T,K;
int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}
int solve1(ll y,int z,int p)
{
	y%=p;
	ll ans=1;
	for(int i=z;i;i>>=1,y=y*y%p)
		if(i&1)ans=ans*y%p;
	return ans;
}
void solve2(int y,int z,int p)
{
	p=-p;
	int t=gcd(y,p);
	if(z%t){puts("Orz, I cannot find x!");return;}
	y/=t;z/=t;p/=t;
	int a,b;exgcd(y,p,a,b);
	a=(ll)a*z%p;
	while(a<0)a+=p;
	printf("%d\n",a);
}
map<int,int> mp;
void solve3(int y,int z,int p)
{
	y%=p;
	if(!y&&!z){puts("1");return;}
	if(!y){puts("Orz, I cannot find x!");return;}
	mp.clear();
	ll m=ceil(sqrt(p)),t=1;
	mp[1]=m+1;
	for(ll i=1;i<m;i++)
	{
		t=t*y%p;
		if(!mp[t])mp[t]=i;
	}
	ll tmp=solve1(y,p-m-1,p),ine=1;
	for(ll k=0;k<m;k++)
	{
		int i=mp[z*ine%p];
		if(i)
		{
			if(i==m+1)i=0;
			printf("%lld\n",k*m+i);
			return;
		}
		ine=ine*tmp%p;
	}
	puts("Orz, I cannot find x!");
}