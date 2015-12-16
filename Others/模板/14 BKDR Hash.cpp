int sd1=1,seed=131,sd2=31;     

int bkdr_hash(int x,string s){
    for (int i=0;i<s.length();i++)           
    x = (x*seed+s[i]-'0'+modnum) % modnum;  
    return x % modnum;
}