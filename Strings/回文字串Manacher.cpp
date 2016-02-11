//回文字串Manacher
void manacher(){ 
	int m = 2 * n + 1;
	for (int i = 1;i <= n;i++){ 
		a[i << 1] = ch[i];
		a[i << 1 | 1] = '#';
	}
	a[0] = '+'; a[1] = '#'; a[m+1] = '-';
	int mx = 0,id;
	for (int i = 1;i <= m;i++){ 
		if (mx >= i) p[i] = min(mx - i,p[2*id-i]);
		else p[i] = 0;
		for (;a[i+p[i]+1] == a[i - p[i]];p[i]++);
		if (p[i] + i > mx) id = i,mx = p[i]+1;
	}
}

