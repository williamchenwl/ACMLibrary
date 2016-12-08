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

    //hint:should be defined in global 
    //all the input array should start at zero
	    
}PString;
