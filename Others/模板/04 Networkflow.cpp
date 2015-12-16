
int sap(int u,int flow){
 
  if (u==T) return flow;      
  
  int tmp,rec=0;
  
  for (int i=base[u];i;i=Nx[i]){
      int x=now[i];   
      if (fl[i]<=0||d[u]!=d[x]+1) continue;
      tmp=sap(x,min(flow-rec,fl[i]));
      rec += tmp; fl[i] -= tmp; fl[op[i]] += tmp;   
      if (rec == flow) return now; 
      }

  if (d[S]>=n) return now;
  
  num[d[u]]--; if (!num[d[u]]) d[S]=n;
  
  num[++d[u]]++;  return now;

}