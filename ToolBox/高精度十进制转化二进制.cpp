int divmod(int x = 2){ 
	for (int i = n - 1;i;--i){ 
		tmp[i - 1] += (tmp[i] % x) * 10;
		tmp[i] /= x;
	}
	int res = tmp[0] % x;
	tmp[0] /= x;	
	for (int i = 0;i < n;i++) tmp[i + 1] += tmp[i];
	while (n && tmp[n - 1]) --n;
	return res;
}

void toBinary(){ 
	for (int i = 0;i < n;i++) tmp[i] = s[i] - '0';
	reverse(tmp,tmp + n);
	++tmp[0];
	m = 0;
	while (n) val[m++] = divmod();
}	