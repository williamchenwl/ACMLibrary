//伸展树Splay.cpp
int tr[80001][2],num[80001],fa[80001];
void rotate(int x,int &k)
{
    int y=fa[x],z=fa[y],l,r;
    if(tr[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else{if(tr[z][0]==y)tr[z][0]=x;else tr[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
}
void splay(int x,int &k)
{
	int y,z;
	while(x!=k)
	{
		y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((tr[y][0]==x)^(tr[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void ins(int &k,int x,int last)
{
	if(k==0){size++;k=size;num[k]=x;fa[k]=last;splay(k,rt);return;}
	if(x<num[k])ins(tr[k][0],x,k);else ins(tr[k][1],x,k);
}
void del(int x)
{
	splay(x,rt);
	if(tr[x][0]*tr[x][1]==0)
	{rt=tr[x][0]+tr[x][1];}
	else 
	{
		int k=tr[x][1];
		while(tr[k][0])k=tr[k][0];
		tr[k][0]=tr[x][0];fa[tr[x][0]]=k;
		rt=tr[x][1];
	}
	fa[rt]=0;
}
void ask_before(int k,int x)
{
	if(k==0)return;
	if(num[k]<=x){t1=k;ask_before(tr[k][1],x);}
	else ask_before(tr[k][0],x);
}
void ask_after(int k,int x)
{
	if(k==0)return;
	if(num[k]>=x){t2=k;ask_after(tr[k][0],x);}
	else ask_after(tr[k][1],x);
}
 
