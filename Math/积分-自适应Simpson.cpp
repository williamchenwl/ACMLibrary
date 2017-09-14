double simpson(double l,double r){  
	return (f(l) + 4 * f((l + r) / 2.0) + f(r)) / 6.0;
}

double rsimpson(double l,double r){   
	double mid = (l + r) / 2.0;
	if (fabs(simpson(l,r) - simpson(l,mid) - simpson(mid,r)) < eps) return simpson(l,mid) + simpson(mid,r);
	return rsimpson(l,mid) + rsimpson(mid,r);
}