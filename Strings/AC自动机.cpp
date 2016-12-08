int son[N][4],w[N],fail[N],id[N],n,L,tot = 0;

int timx = 0;

int init(){
	tot = 0;
	memset(son,0,sizeof(son));
	memset(fail,0,sizeof(fail));
	memset(id,0,sizeof(id));
}
   
int mapp(char ch){
	if (ch == 'A') return 0;
	if (ch == 'T') return 1;
	if (ch == 'C') return 2;
	else return 3;
}

int ins(string s,int p){
	for (int l = s.length(),x = 0,i = 0,w;i < l;i++){
		if (!son[x][w = mapp(s[i])]) son[x][w] = ++tot;
		x = son[x][w];
		if (i == l - 1) id[x] |= (1 << p);
	}
}

int q[N];

void build(){
	int h = 1,t = 0,i,j,x; fail[0] = -1;
	for (int i = 0;i < 4;i++)
	if (son[0][i]) q[++t] = son[0][i];
	while(h <= t)for(x = q[h++],i = 0;i < 4;i++){
	if (son[x][i]){ 
		fail[son[x][i]] = son[fail[x]][i];
		q[++t] = son[x][i];
		id[son[x][i]] |= id[fail[son[x][i]]];
	}
	else son[x][i] = son[fail[x]][i];
	}
}