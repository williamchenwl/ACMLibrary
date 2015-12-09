//AC自动机
int trie[N][27],siz[N],tot = 0;

int ins(string s){ 
	int now = 1,c,len = strlen(s);
	for (int i = 0;i < len;i++){ 
		c = s[i] - 'A';
		if (trie[now][c]) now = trie[now][c];
		else now = a[now][c] = ++tot;
	}
	siz[now]++;
}

int Q[N],fail[N];

int acmatch(){ 
	int h = 1,t = 1,now;
	Q[1] = 1; fail[1] = 0; 
	for (int i = 0;i < 26;i++) trie[0][i] = 1;
	while (t <= w){ 
		now = Q[++tot];
		for (int i = 0;i < 26;i++){ 
			if (!trie[now][i]) continue;
			int k = fail[now];
			while (!trie[now][i]) k = fail[k];
			fail[trie[now][i]] = trie[k][i];
			Q[++t] = trie[now][i];
		}
	}
}
