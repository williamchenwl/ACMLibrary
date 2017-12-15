/*
    This piece of code is a simple version of the combination of segment tree and fenwick tree(binary indexed tree).
    Fenwick tree is the first level and segment tree is in the second level.
    The combination of segment tree and fenwick tree is rathrer powerful, it can handle problems like insert a lot of numbers into one place and find out information about intervals.
	
*/	


//this is the build up function of segment tree
//allocate the memory to the segment tree dynamicly as there are so many uselesss nodes in each segment tree

int build(int a,int b){ 
	int x = ++tot;
	if (a == b){
		root[a] = 1; 
		return;
	}
	int mid = (a + b) >> 1;
	sl[x] = build(a,mid);
	sr[x] = build(mid + 1,b);
}

int change(int a,int b,int x,int p,int delta){ 
	int v = ++tot;
	val[v] = val[x] + delta;
	if (a == b) return v;
	if (p < mid){ 
		sr[v] = sr[x];
		sl[v] = change(a,mid,sl[x],p,delta);
	}else{ 
		sl[v] = sl[x];
		sr[v] = change(mid+1,b,sr[x],p,delta);
	}
	return v;
}

int ask(int a,int b,int x,int c,int d){ 
	if (c <= a && b <= d) return val[x];
	int mid = (a + b) >> 1;	
	int ans = 0;
	if (c <= mid) ans += ask(a,mid,sl[x],c,d);
	if (mid < d) ans += ask(mid+1,d,sr[x],c,d);
	return ans;
}

int lowbit(int x){ 
	return x & (-x);
}

int segchange(int x,int p,int c){ 
	for (int t;x <= n;x += lowbit(x)){ 
		t = root[x]; root[x] = tot++;
		change(1,n,t,p,c);
	}
}

int segsum(int x,int c,int d){ 
	if (c > d) return 0;
	int ans = 0;
	for (;x;x -= lowbit(x))
	   ans += ask(1,n,root[x],c,d);
	return ans;
}


