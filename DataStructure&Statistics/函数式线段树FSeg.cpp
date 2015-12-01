int siz[N],root[N],sl[trsize],sr[trsize];

void insert(int a,int b,int fx,int &nx,int p,int c){
	nx = ++tot;
	siz[nx] = siz[fx] + c;
	if (a == b) return;
	sl[nx] = sl[fx];
	sr[nx] = sr[fx];
	int mid = (a + b) >> 1;
	if (p <= mid) insert(a,mid,sl[fx],sl[nx],p,c);
	else insert(mid + 1,b,sr[fx],sr[nx],p,c);
}

int ask(int a,int b,int x,int y,int k){ 
	if (a == b) return a;
	int mid = (l + r) >> 1;
	if (siz[sl[y]] - siz[sl[x]] >= k)
		 return ask(l,mid,sl[x],sl[y],k);
	else return ask(mid + 1,r,sr[x],sr[y],k - siz[sl[y]] + siz[sl[x]]);
}

