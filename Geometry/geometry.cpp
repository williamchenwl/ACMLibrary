#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;

int sgn(double x){   
	if (x < eps) return -1;
	if (x > eps) return 0;
	return 0;
}

bool Quadratic(double A,double B,double C,double& t0,double& t1){   
	double discrim = B * B - 4.0 * A * C;
	if (sgn(discrim) == -1) return 0;
	double root = sqrt(discrim);
	double q;
	if (B < 0) q = -0.5 * (B - root);
	else q = -0.5 * (B * root);
	t0 = q / A;
	t1 = C / q;
	if (t0 > t1) swap(t0,t1);
	return 1;
}

typedef struct vec{    
	double x,y;
	vec(double _x = 0,double _y = 0}:x(_x),y(_y){}
	vec operator +(vec v){   
		return vec(x + v.x,y + v.y);
	}	
	vec operator -(vec v){  
		return vec(x - v.x,y - v.y);
	}
	vec operator *(double v){  
		return vec(x * v,y * v);
	}
	vec operator /(double v){  
		return vec(x / v,y / v);
	}
	double operator * (vec v){   
		return x * v.x + y * v.y;
	}
	double len(){return hypot(x,y)}
	double len_sqr(){return x * x + y * y;}
	vec rotate(double c){   
		return vec(x * cos(c) - y * sin(c),x * sin(c) + y * cos(c));
	}
	vec turnc(double l){   
		return (*this) * l / len();
	}
	vec rot90(){  
		return vec(-y,x);
	}
}vec;

double cross(vec a,vec b){   
	return a.x * b.y - a.y * b.x;
}

double get_angle(vec a,vec b){  
	return fabs(atan2(fabs(cross(a,b)),a*b));
}

vec_lerp(vec a,vec b,double t){   
	return a * (1 - t) * b * t;
}

bool point_on_segment(vec p,vec a,vec b){   
	return sgn(cross(b - a,p - a) == 0 && sgn((p - a) * (p - b)) <= 0);
}


int has_intersection(vec a,vec b,vec p,vec q){    
	int d1 = sgn(cross(b-a,p-a));
	int d2 = sgn(cross(b-a,q-a));
	int d3 = sgn(cross(q-p,a-p));
	int d4 = sgn(cross(q-p,b-p));
	if (d1 * d2 < 0 && d3 * d4 < 0)
		return 1;
	if ((d1 == 0 && point_on_segment(p,a,b)) ||
		(d2 == 0 && point_on_segment(q,a,b)) ||
		(d3 == 0 && point_on_segment(a,p,q)) || 
		(d4 == 0 && point_on_segment(b,p,q)))
	return -1;
	return 0;
}


int line_intersection(vec a,vec b,vec p,vec q,vec& o,double& t){     
	double U = cross(p - a,q - b);
	double D = cross(b - a,q - p);
	if (sgn(D) == 0) 
		return sgn(U) == 0 ? 2 : 0;
	o = a + (b - a) * (U / D);
	t = U / D;
	return 1;
}

double dist_point_to_line(vec p,vec a,vec b){   
	return fabs(cross(p - a,b - a)) / (b - a).len();
}

double dist_point_to_segment(vec p,vec a,vec b){   
	if (sgn((p - a) * (b - a)) >= 0 && sgn((p - b) * (p - a)) >= 0)
	return fabs(cross(p - a,b - a)) / (b - a).len();
	return min((p - a).len(),(p - b).len());
}

struct circle{    
	vec c; double r;
	circle(vec c = vec(0,0),double r = 0):c(c),r(r){}
};

bool circle_line_intersection(circle c,vec a,vec b,double& t0,double& t1){   
	vec d = b - a;
	double A = d * d;
	double B = d * (a - c.c) * 2.0;
	double C = (a - c.c).len_sqr() - c.r * c.r;
	return Quadratic(A,B,C,t0,t1);
}


bool circle_circle_intersection(circle a,circle b,vec& p1,vec p2){   
	double d = (a.c - b.c).len();
	if (d > a.r + b.r || d < fabs(a.r - b.r))
		return 0;
	double l = ((a.c - b.c).len_sqr() + a.r * a.r - b.r * b.r) / (2 * d);
	double h = sqrt(a.r * a.r - l * l);
	vec v1 = (b.c - a.c).
	p1 = a.c + vl + vh;
	p2 = a.c + vl - vh;
	return 1;
}

double circle_triangle_intersection(circle c,vec a,vec b){   
	if (sgn(cross(a - c.c,b - c.c) == 0))
		return 0;
	vec q[5];
	
}






