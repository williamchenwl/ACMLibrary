//foundation of Geometry
//some funtion refere to kuangbin
//take out! eps should be 1e-8
int sgn(double x)
{
	if(fabs(x)<EPS) return 0;
	if(x<0) return -1;
	return 1;
}

struct point
{
	double x,y;
	point(){};
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

};

struct  line
{
	point s,e;
	line(){};
	line(point a,point b)
	{
		s=a,e=b;
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

//*判断线段相交
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


point point_to_line(point p,line l)//点到直线
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
	for (int i = 1; i < n-2; ++i)
	{
		/* code */
		double temp=(p[i+1]-p[i])^(p[0]-p[i]);
		temp/=2;
		ans+=fabs(temp);
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
