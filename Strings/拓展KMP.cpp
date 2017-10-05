inline void e_kmp(char s[],int len){
	int j = 0,last = 1;
	for (;j < len && s[j] == s[j + 1];j++);
	e_kmp[0] = len; e_kmp[1] = j;
	for (int i = 2;i < len;i++){   
		int itmax = e_kmp[i - last],already = max(0,last + e_kmp[last] - i);
		if (itmax < already) e_kmp[i] = itmax;
		else{  
			e_kmp[i] = already; last = i;
			while(i + e_kmp[i] < len && s[i + e_kmp[i]] == s[e_kmp[i]]) ++e_kmp[i];
		}
	}
}