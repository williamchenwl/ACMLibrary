

int siz[N],root[N],sl[trsize],sr[trsize];

/*
	cover a single place('p') with 'c' times 
	fx is the pre-version of segment tree and the corresponding node
	nx is the new-version of segment tree
	a and b is passed to determine which node(left or right) to go in the next step, they together represent the interval of the c current node.
*/

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
	int mid = (a + b) >> 1;
	if (siz[sl[y]] - siz[sl[x]] >= k)
		 return ask(a,mid,sl[x],sl[y],k);
	else return ask(mid + 1,b,sr[x],sr[y],k - siz[sl[y]] + siz[sl[x]]);
}

