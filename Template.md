[TOC]



## Glory-ICPC-2017-Template

#### 1.字符串

##### 1.1 AC自动机

多组数据必须调用init()，结构为trie图，根节点为0

```c++
int son[N][4],w[N],fail[N],id[N],n,L,tot = 0;
   
int mapp(char ch){
	return ch - 'a';
}

void clearnd(int x){  
	memset(son[x],0,sizeof(son[x]));
	id[x] = fail[x] = 0;
}

int init(){
	tot = 0;
	clearnd(0);
	clearnd(1);
}

int ins(string s,int p){
	for (int l = s.length(),x = 0,i = 0,w;i < l;i++){
		if (!son[x][w = mapp(s[i])]){ 
			son[x][w] = ++tot;
			clearnd(tot);
		}
		x = son[x][w];
		if (i == l - 1) id[x] |= (1 << p);
	}
}

int q[N];

void build(){
	int h = 1,t = 0,i,j,x; fail[0] = -1;
	for (int i = 0;i < 26;i++)
	if (son[0][i]) q[++t] = son[0][i];
	while(h <= t)for(x = q[h++],i = 0;i < 26;i++){
		if (son[x][i]){ 
			fail[son[x][i]] = son[fail[x]][i];
			q[++t] = son[x][i];
			//id[son[x][i]] |= id[fail[son[x][i]]];
		}
		else son[x][i] = son[fail[x]][i];
	}
}

int ask(const string& s){  
	int ans = 0;
	for (int l = s.length(),x = 0,w,i = 0;i < l;i++){  
		w = mapp(s[i]);
		x = son[x][w];
		for (int j = x;j && id[j] != -1;j = fail[j]){  
			ans += id[j];
		}
	}
}
```



##### 1.2 KMP



```c++
typedef struct PString{
    
    typedef char dtype;

    dtype s[N];

    int p[N],len,flag;

    std::vector<int>v;

    int OnCreate(dtype ss[],int lenx){
        len = lenx;
        for (int i = 0;i < lenx;i++) s[i] = ss[i];
        int j = -1; p[0] = -1;
        for (int i = 1;i < len;i++){
            while (s[i] != s[j + 1] && j != -1) j = p[j];
            if (s[i] == s[j + 1]) j++;
            p[i] = j;
        }
    }

    int kmp(dtype pa[],int lenx){
        int j = -1;
        for (int i = 0;i < lenx;i++){
            while (pa[i] != s[j + 1] && j != -1) j = p[j];
            if (pa[i] == s[j + 1]) j++;
            if (j == len - 1) ans++,flag = 1,j = p[j];
        }
        return flag;
    }
  
}PString;
```

