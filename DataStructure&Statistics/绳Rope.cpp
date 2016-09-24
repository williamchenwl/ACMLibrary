/*
    correctly used times = 
    used in = { 
    
    }
*/
//绳Rope
#include<iostream>
#include<cstdio>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
crope list;
int t,now;
char ch[3000005];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main()
{
    t=read();
    char s[10];int x;
    while(t--)
    {
        scanf("%s",s);
        switch(s[0])
        {
        case 'M':now=read();break;
        case 'P':now--;break;
        case 'N':now++;break;
        case 'I':
            x=read();
            for(int i=0;i<x;i++)
            {
                ch[i]=getchar();
                while(ch[i]=='\n')ch[i]=getchar();
            }
            ch[x]=0;
            list.insert(now,ch);
            break;
        case 'D':x=read();list.erase(now,x);break;
        case 'G':x=read();list.copy(now,x,ch);ch[x]=0;puts(ch);
        }
    }
    return 0;
}
