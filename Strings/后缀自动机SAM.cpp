//后缀自动机


int last = 1,tot = 1;
void add(int w){
	int p = ++tot,x = last,r,q;
	ml[last = p] = ml[x] + 1;
	for (;x && !son[x][w];x = pre[x]) son[x][w] = p;
	if (!x) {pre[p] = 1; return;}
	if (ml[x] + 1 == ml[q = son[x][w]]) {pre[p] = q; return;}
	pre[r = ++tot] = pre[q];
	memcpy(son[r],son[q],sizeof son[r]);
	ml[r] = ml[x] + 1;.
	pre[p] = pre[q] = r;
	for (;x && son[x][w] == q;x = pre[x]) son[x][w] = r;
}
