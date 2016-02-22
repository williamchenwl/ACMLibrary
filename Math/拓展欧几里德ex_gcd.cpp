/*
    correctly used times = 
    used in = { 
   	
    }
*/
//扩展欧几里得
ll ex_gcd(ll a,ll b,ll &x,ll &y){ 
	if (!b) return x = 1,y = 0,a;
	int gcd = ex_gcd(b,a % b,x,y);
	int t = x; x = y; y = t - a / b *y;
	return gcd;
}

