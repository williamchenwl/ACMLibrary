

int scan(int&a){
  while(!((ch=getchar())>='0')&&(ch<='9'));
  a=ch-'0';
  while(((ch=getchar())>='0')&&(ch<='9'))a*=10,a+=ch-'0';

}
