/*
	functional style segment tree is a very useful and simple data structure.
	the basic idea of this data structure is saving all the history information with minimum cost of memory.
	With this data structure, you can create a segment tree representing the value information of an interval as long as the value information can be obtained with the subtract operation. 
*/



const int trsize = N * 20;

/*
	siz : the value infomation, how many covers there are of the current node.
	root : representing the root node id of one history version of the segment tree.
	sl : left-son of the segment-tree node
	sr : right-son of the segment-tree node
*/

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
