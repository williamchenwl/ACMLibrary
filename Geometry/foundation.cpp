/*
    correctly used times = 
    used in = { 
   	
    }
*/
//foundation of Geometry
//some funtion refere to kuangbin
//take out! eps should be 1e-8
const double EPS = 1e-8
const double PI = acos(-1.0);
int sgn(double x)
{
	if(fabs(x)<EPS) return 0;
	if(x<0) return -1;
	return 1;
}
struct point
{
	double x,y; point(){};
	point (double x0,double y0)
	{
		x=x0,y=y0;
	}
	point operator - (const point &b)const
	{
		return point(x-b.x,y-b.y);
	}
	point operator + (const point &b)const
	{
		return point(x+b.x,y+b.y);
	}
	double operator * (const point &b) const
	{
		return x*b.x+y*b.y;
	}
	double operator ^ (const point &b) const
	{
		return x*b.y-y*b.x;
	}

	void transXY(double B)//Counterclockwise
	{
		double tx=x,ty=y;
		x = tx*cos(B)-ty*sin(B); y = tx*sin(B)+ty*cos(B);
	}

	bool operator == (const point &b)const
    {
        return (sgn(x-b.x)==0 && sgn(y-b.y)==0);
    }
    double len()
    {
        double t = x*x + y*y;
        return sqrt(t);
    }
    point unit()
    {
        double l = len();
        double xx = x/l;
        double yy = y/l;
        return point(xx,yy);
    }
    point neg()
    {
        return point(-x,-y);
    }


};


struct line
{
	point s,e; line(){};
	line(point a,point b)
	{
		s=a,e=b;
	}
	pair<int ,point> operator &(const line &b)const//two line insert
	{
		point res=s;
		if(sgn((s-e)^(b.s-b.e))==0)// parallel
		{
			if(sgn((s-b.e)^(b.s-b.e))==0) return make_pair(0,res);//coincide
			else
			return make_pair(1,res);
		}
		double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e)); res.x += (e.x-s.x)*t;
		res.y += (e.y-s.y)*t; 
		return make_pair(2,res);
	}


	for(int i=0;i<4;i++)
    {
        line t(A[i],A[(i+1)%4]);
        l1.pb(t);
    }
	point v;
    point get_point(double t)// used in rush(line and circle insert)
    {
        return point(s.x+v.x*t,s.y+v.y*t);
    }

};

struct  circle
{
	point heart;
	double r;

};

double dist(point a,point b)
{
	double xx=(a.x-b.x),yy=(a.y-b.y);
	return sqrt(xx*xx+yy*yy);
}

bool _cmp(point p1,point p2) //相对于P【0】j极角排序
{  
	double tmp = (p1-list[0])^(p2-list[0]);  
	if(sgn(tmp) > 0)
		return true;  
	else if(sgn(tmp) == 0 && sgn(dist(p1,list[0]) - dist(p2,list[0])) <= 0)   
		return true;  
	else return false; 
}
point rush(circle c,line l,bool &flag)//圆与直线交点
{
    double a = l.v.x;
    double b = l.s.x - c.heart.x;
    double cc = l.v.y;
    double d = l.s.y - c.heart.y;

    double e = a*a+cc*cc;
    double f = 2*(a*b+cc*d);
    double g = b*b+d*d-c.r*c.r;
    double delta = f*f-4*e*g;
    if(sgn(delta)<=0)
    {
        flag = 0;
        return point(0,0);
    }
    else{
        double t = (-f-sqrt(delta))/(2*e);///////////////
        flag = 1;
        return l.get_point(t);
    }
}

//判断线段相交
bool inter(line l1,line l2)
{
	return
	max(l1.s.x,l1.e.x) >= min(l2.s.x,l2.e.x) &&
    max(l2.s.x,l2.e.x) >= min(l1.s.x,l1.e.x) &&
    max(l1.s.y,l1.e.y) >= min(l2.s.y,l2.e.y) &&
    max(l2.s.y,l2.e.y) >= min(l1.s.y,l1.e.y) &&
    sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e)) <= 0 &&
    sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e)) <= 0;
}

bool Seg_inter_line(line l1,line l2)//line l1与seg l2是否相交
{
	return sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0;
}

point point_to_line(point p,line l)//点到直线距离
{
	point ret;
	double t=(l.e-l.s)*(p-l.s)/dist(l.s,l.e);
	ret.x=l.s.x+(l.e.x-l.s.x)*t;
	ret.y=l.s.y+(l.e.y-l.s.y)*t;
	return ret;
}

point point_to_segline(point p,line l) //点到线段距离
{
	point ret;
	double t=(l.e-l.s)*(p-l.s);
	t=fabs(t)/dist(l.s,l.e)/dist(l.s,l.e); 
	if(t>=0&&t<=1)
	{
		ret.x=l.s.x+(l.e.x-l.s.x)*t;
		ret.y=l.s.y+(l.e.y-l.s.y)*t;
	}
	else
	{
		if(dist(p,l.s)<dist(p,l.e)) 
			ret=l.s;
		else
			ret=l.e;
	}
	return ret;
}


double areaMulti(point p[],int n)//计算多边形
{
	double ans=0;
	for (int i = 1; i < n; ++i)
	{
		/* code */
		ans += (p[i]^p[(i+1)%n])/2; 
	}
	return ans;
}

bool onSeg(point p,line l)
{
	return
	sgn(((l.s-p)^(l.e-p))==0)&&
	sgn(((p.x-l.s.x)*(p.x-l.e.x))<=0)&&
	sgn(((p.y-l.s.y)*(p.y-l.e.y))<=0);
}
/*
点是否在凸边形内，-1外，0上个，1内
*/
int inConvexPoly(point a,point p[],int n)
{
	for(int i = 0;i < n;i++)
	{
		if(sgn((p[i]-a)^(p[(i+1)%n]-a))<0) return -1;
		else if(onSeg(a,line(p[i],p[(i+1)%n]))) return 0;

	}
	return 1;
}

/*
点是否在多边形内，是1，否-1，边界上0
*/
int inPoly(point p,point poly[],int n)
{
	int cnt=0;
	line ray,side;
	ray.s=p;
	ray.e.y=p.y;
	ray.e.x=-(double)INF;
	for (int i = 0; i < n; ++i)
	{
		/* code */
		side.s=poly[i];
		side.e=poly[(i+1)%n];
		if (onSeg(p,side))
		{
			return 0;
		}

		if(sgn(side.s.y-side.e.y)==0)
			continue;

		if(onSeg(side.s,ray))
		{
			if(sgn(side.s.y-side.e.y)>0)
				cnt++;
		}
		else if(onSeg(side.e,ray))
		{
			if(sgn(side.e.y-side.s.y)>0)
				cnt++;
		}
		else if(inter(ray,side))
			cnt++;


	}
	if(cnt%2==1)
		return 1;
	else
		return -1;
}

/*
判断是否是凸边形
*/
bool inConvex(point poly[],int n)
{
	bool s[3];
	memset(s,0,sizeof(s));
	for(int i=0;i<n;i++)
	{
		s[sgn((poly[(i+1)%n]-poly[i])^(poly[(i+2)%n]-poly[i]))+1] = 1;
		if(s[0]&&s[2]) return 0;
	}
	return 1;
}

//两个圆的公共部分面积
double Area_of_overlap(Point c1,double r1,Point c2,double r2)
{
	double d = dist(c1,c2);
	if(r1 + r2 < d + eps)return 0;
	if(d < fabs(r1 - r2) + eps)
	{
		double r = min(r1,r2);
		return PI*r*r;
	}
	double x = (d*d + r1*r1 - r2*r2)/(2*d);
	double t1 = acos(x / r1);
	double t2 = acos((d - x)/r2);
	return r1*r1*t1 + r2*r2*t2 - d*r1*sin(t1);
}

/*
三点求圆心坐标（三角形外心）
*/

point waixin(point a,point b,point c)
{
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1)/2;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2)/2;
	double d = a1*b2 - a2*b1;
	return point(a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d);
}


/*
半平面交 （From UESTC）
直线左边代表有效区域
*/

bool HPIcmp(line a,line b)
{
	if(fabs(a.k-b.k)>eps) return a.k<b.k;
	return ((a.s-b.s)^(b.e-b.s))<0;
}
line Q[110];
void HPI(line l[],int n,point res[],int &resn)
{
	int tol=n;
	sort(l,l+n,HPIcmp);
	tol=1;
	for(int i=1;i<n;i++)
		if(fabs(l[i].k-l[i-1].k)>EPS)
			l[tol++]=l[i];
	int head=0,tail=1;
	Q[0] = l[0];
	Q[1] = l[1];
	resn=0;
	for(int i=2;i<tol;i++)
	{
		if(fabs((Q[tail].e-Q[tail].s)^(Q[tail-1].e-Q[tail-1].s)) < eps ||
		 fabs((Q[head].e-Q[head].s)^(Q[head+1].e-Q[head+1].s)) < eps) 
		    return;  
	 	while(head < tail && (((Q[tail]&Q[tail-1]) - line[i].s)^(line[i].e-line[i].s)) > eps)
	 	    tail--;   
	 	while(head < tail && (((Q[head]&Q[head+1]) - line[i].s)^(line[i].e-line[i].s)) > eps)    
	 		head++;   
	 	Q[++tail] = line[i];
	}
	while(head < tail && (((Q[tail]&Q[tail-1]) - Q[head].s)^(Q[head].e-Q[head].s)) > eps)   
		tail--;  
	while(head < tail && (((Q[head]&Q[head-1]) - Q[tail].s)^(Q[tail].e-Q[tail].e)) > eps)   
		head++;  
	if(tail <= head + 1)
		return;  
	for(int i = head; i < tail; i++)   
		res[resn++] = Q[i]&Q[i+1];  
	if(head < tail - 1)   
		res[resn++] = Q[head]&Q[tail];

}