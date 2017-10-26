#include <bits/stdc++.h>

using namespace std;

int nowx;

const int N = 2100000;

typedef long long ll;

struct circle{
	int x,y;
	ll r;
	circle(){}
	circle(int _x,int _y,int _r):x(_x),y(_y),r(_r){}
};

circle C[N];

struct qu{
    int x,ty,id;
    qu(){}
    qu(int _x,int _ty,int _id):x(_x),ty(_ty),id(_id){}
    bool operator<(const qu& a)const{
        if (a.x != x) return x < a.x;
        else return ty < a.ty;
    }
};

qu q[N * 2];

int col[N];

double posx(int id,int ty){
		double delta = nowx - C[id].x;
		delta = delta * delta;
		delta = (double)C[id].r * (double)C[id].r - delta;
		delta = sqrt(delta);
		return C[id].y + ty * delta;
}

typedef struct seg{
	int id,ty;

	seg(int _id,int _ty):id(_id),ty(_ty){}

	bool operator <(const seg& a)const{
		double p1 = posx(id,ty);
		double p2 = posx(a.id,a.ty);
		if (p1 != p2) return p1 < p2;
		else return ty < a.ty;
	}
}seg;

set<seg>S;

int n;

int main(){
	while(cin >> n){
		int tot = 0;
		for (int i = 1;i <= n;i++){
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
            C[i] = circle(x,y,c);
            q[++tot] = qu(x-c,1,i);
            q[++tot] = qu(x+c,-1,i);
		}

		sort(q+1,q+tot+1);
		S.clear();
		col[0] = -1;
		for (int i = 1;i <= tot;i++)if(q[i].ty==1){
            nowx = q[i].x;
		    if(!S.empty()){
                set<seg>::iterator itr;
                itr = S.upper_bound(seg(q[i].id,1));
                if (itr == S.end()){
                    col[q[i].id] = 1;
                }else{
                    seg ng = *itr;
                    if (ng.ty == 1){
                        col[q[i].id] = -col[ng.id];
                    }else col[q[i].id] = col[ng.id];
                }
		    }else col[q[i].id] = 1;
			S.insert(seg(q[i].id,1));
			S.insert(seg(q[i].id,-1));
		}else{
		    nowx = q[i].x;
			S.erase(seg(q[i].id,1));
			S.erase(seg(q[i].id,-1));
		}

		long long ans = 0;
		for (int i = 1;i <= n;i++){
            ans = ans + (long long)C[i].r * (long long)C[i].r * col[i];
		}
		cout << ans << endl;
	}
}
