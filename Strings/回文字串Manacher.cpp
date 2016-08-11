/*
    correctly used times = 
    used in = { 
   		hdu3068,
    }
*/
//回文字串Manacher

int manacher(){
	int m = 2 * n + 1;
	
	for (int i = 1;i <= n;i++){
		a[i << 1] = s[i-1];
		a[(i << 1) + 1] = '#';
	}
	
	a[0] = '+'; a[1] = '#'; a[m + 1] = '-';

	int mx = 0,id;
	for (int i = 1;i <= m;i++){
		if (mx >= i) p[i] = min(mx - i,p[2 * id - i]);
		else p[i] = 0;
		while(a[i + p[i] + 1] == a[i - p[i] - 1]) p[i]++;
		if (p[i] + i > mx) id = i,mx = p[i] + i;
	}

	int ans = 0;
	for (int i = 1;i <= m;i++) if (p[i] > ans) ans = p[i];
	return ans;
}


