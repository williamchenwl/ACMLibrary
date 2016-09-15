void getprim(){
	//initializing
	for (int i = 2;i < N;i++)if(!prim[i]){
		pri.push_back(i);
		for (int j = 2 * i;j < N;j += i)
			prim[j] = 1;
	}
}

ll mou(int x){
	ll ans = 1;
	for (int i = 0;i < pri.size() && pri[i] <= x;i++)
		if (x % pri[i] == 0){
			if (x % (pri[i] * pri[i]) == 0)
				return 0;
			ans *= -1;
			x /= pri[i];
		}
	if (x != 1) ans *= -1;
	return ans;
}