//莫队算法
typedef struct que{ 
	int l,r,id;
}que;

que qu[N];

bool cmp(que a,que b){ 
	if (pos[a.l] == pos[b.l]) return a.r < b.r;
	return a.l < b.l;
}

int bkn;

int init(){ 
	bkn = int(sqrt(n));
	for (int i = 1;i <= n;i++)
		pos[i] = (i - 1)/bkn + 1;
}
