while (l < r){ 
	int mid = (l + r) >> 1;
	if (f(mid) >= f(mid+1))
		r = mid,ans = max(ans,f(mid));
	else l = mid + 1;
}

