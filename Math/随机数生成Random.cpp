/*
    correctly used times = 
    used in = { 
   	
    }
*/
//随机数生成
typedef struct Random{ 
 	
 	int seed,modnum,now;

 	int init(int x,int y){ 
 		seed = x;
 		modnum = y;
 		now = seed;
 	}

 	int getRand(){ 
 		now = (now * 31 + 997) % modnum;
        return now;
 	}
}Ran;
