 /*
    ID 02
    build fail point;
 */

 int insert(int p){

  for(int l=strlen(s),x=0,i=0,w;i<l;i++){
    w=s[i]-'a';
    if(!son[x][w]) son[x][w]=++tot;
    x=son[x][w];
    if(i==l-1) id[x]=p;
  }
}

inline void make(){
  int h=1,t=1,i,j,x;fail[0]=-1;

  while(h<=t)
  for(x=q[h++],i=0;i<26;i++)
  if(son[x][i])
  for(q[++t]=son[x][i],j=fail[x];~j;j=fail[j])
  if(x&&son[j][i]){fail[son[x][i]]=son[j][i];break;}

}


inline void find(){
  for(int l=strlen(s),x=0,i=0,w,j;i<l;i++){
    w=s[i]-'a';
    while(x&&!son[x][w])x=fail[x];
    x=son[x][w];
    for(j=x;j;j=fail[j])if(id[j])printf("%d ",id[j]);
  }
}
