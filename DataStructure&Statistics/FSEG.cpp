const int trsize = N * 20;

ll siz[trsize];
int root[N],sl[trsize],sr[trsize],tot = 0;

void insertx(int a,int b,int fx,int &nx,int p,ll c){
	nx = ++tot;
	siz[nx] = siz[fx] + c;
	if (a == b) return;
	sl[nx] = sl[fx];
	sr[nx] = sr[fx];
	int mid = (a + b) >> 1;
	if (p <= mid) insertx(a,mid,sl[fx],sl[nx],p,c);
	else insertx(mid + 1,b,sr[fx],sr[nx],p,c);
}

ll ask(int a,int b,int x,int y,int low,int high){
	if (a >= low && b <= high) return siz[y] - siz[x];
	int mid = (a + b) >> 1;
	ll ans = 0;
	if (mid >= low) ans += ask(a,mid,sl[x],sl[y],low,high);
	if (mid + 1 <= high) ans += ask(mid+1,b,sr[x],sr[y],low,high);
	return ans;
}
