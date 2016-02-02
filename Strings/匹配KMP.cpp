 
//KMP
typedef struct PString{
    char s[N];

    int p[N],len;

    int OnCreate(){
        len = strlen(s);
        int j = -1; p[0] = -1;
        for (int i = 1;i < len;i++){
            if (s[i] != s[j + 1] && j != -1) j = p[j];
            if (s[i] == s[j + 1]) j++;
            p[i] = j;
        }
    }

    int kmp(char pa[]){
        int lenx = strlen(pa);
        int j = -1;
        for (int i = 0;i < lenx;i++){
            if (pa[i] != s[j + 1] && j != -1) j = p[j];
            if (pa[i] == s[j + 1]) j++;
            if (j == len - 1) return 1;
        }
        return 0;
    }

}PString;
