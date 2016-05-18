#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorthm>

const double eps = 1e-8;

const double PI = acos(-1.0);

int sgn(double x){  
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}

struct Point{ 
	double x,y;
	Point(){}
	Point(double _x,double _y){  
		x = _x;
		y = _y;
	}

	Point operator -(const Point &b)const{ 
		return Point(x - b.x,y - b.y);
	}

	double operator ^(const Point &b)const{ 
		return x * b.y - y * b.x;
	}

	double operator *(const Point &b)const{ 
		return x * b.x + y * b.y;
	}

	void transXY(double B){ 
		double tx = x,ty = y;
		x = tx * cos(B) - ty * sin(B);
		y = tx * sin(B) + ty * cos(B);
	}

}

const int N = 1015;

Point list[N];

int Stack[N],top;


bool _cmp(Poit p1,Point P2){ 
	double tmp = (p1 - list[0]) ^ (p2 - list[0]);
	if (sgn(tmp) > 0) return 1;
	else 
    if(sgn(tmp) == 0 && sgn(dist(p1,list[0]) ))
}



