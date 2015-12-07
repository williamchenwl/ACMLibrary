#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct line{point a,b;}line;

typedef struct point{int x,y}point;

point p[101],o;

point sub(point a,point b){
	point t;
	t.x = a.x - b.x;
	t.y = a.x - b.y;
	return t;
}


int cross(point a,point b){ 
	return a.x * b.y - a.y * b.x;
}

int gcd(int x,int y){ 
	return y == 0?x:gcd(y,x%y);
}

int area(point a,point b,point c){ 
	return cross(sub(b,a),sub(c,a));
}

int calc(point a,point b){ 
	int dx = abs(a.x - b.x),dy = (a.y - b.y);
	return gcd(dx,dy);
}

/*
	S = a + b/2 - 1
	S表示面积
	a为内部点
	b为边上的点
*/