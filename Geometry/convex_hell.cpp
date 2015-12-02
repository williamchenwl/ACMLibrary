凸包


注意凸包的判重和退化

struct point
{
	double x,y;
};

double det(point a,point b,point c,point d)
{
	double x1=b.x-a.x,y1=b.y-a.y;
	double x2=d.x-c.x,y2=d.y-c.y;
	return x1*y2-x2*y1;
}
double dot(point a,point b,point c,point d)
{
	double x1=b.x-a.x,y1=b.y-a.y;
	double x2=d.x-c.x,y2=d.y-c.y;
	return x1*x2+y1*y2;
}
double dist(point a,point b)
{
	double xx=(a.x-b.x)*(a.x-b.x);
	double yy=(a.y-b.y)*(a.y-b.y);
	return sqrt(xx+yy);
}
point ps[100000+5];
int N;
bool cmp_x(const point &a,const point &b)
{
	if(a.x!=b.x)
	{
		return a.x<b.x;
	}
	else{
		return a.y<b.y;
	}	
}
vector<point> convex_hull(point *ps,int n)
{

	sort(ps,ps+N,cmp_x);
	int k=0;
	vector<point>qs(2*n);
	for(int i=0;i<n;i++)
	{
		while(k>1&&(det(qs[k-2],qs[k-1],qs[k-1],ps[i])<=0))
			k--;

		qs[k++]=ps[i];
	}
	for(int i=n-2,t=k;i>=0;i--)
	{
		while(k>t&&(det(qs[k-2],qs[k-1],qs[k-1],ps[i])<=0))
			k--;

		qs[k++]=ps[i];
	}
	qs.resize(k-1);
	return qs;
}
double area(point a,point b,point c)
{
	double ans=det(b,a,b,c);
	return fabs(ans)/2;
}
void solve()
{
	vector<point >qs=convex_hull(ps,N);
	
	

}
旋转卡壳法

int i=0,j=0;
		
		int n=qs.size();
		for(int k=0;k<n;k++)
		{
			if(!cmp_x(qs[i],qs[k])) i=k;
			if(cmp_x(qs[j],qs[k])) j=k;
		}
		int si=i,sj=j;
		while(i!=sj||j!=si)
		{
			//double xa=qs[i].x,ya=qs[i].y,xb=qs[j].x,yb=qs[j].y;
			//double f1=check(x1,y1,x2,y2,xa,ya);
			//double f2=check(x1,y1,x2,y2,xb,yb);
			//if(f1*f2<=0)
			//{flag=0;break;}
			if(det(qs[i],qs[(i+1)%n],qs[j],qs[(j+1)%n])<0)
			i=(i+1)%n;
			else
			j=(j+1)%n;
		}
