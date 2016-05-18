template<class T>

//非负整数
void scan_(T & ret){ 
	char c; ret = 0;
	while((c = getchar()) < '0' || c > '9');
	while(c >= '0' && c <= '9') ret = ret * 10 + (c - '0'),c = getchar();
}

cout.precision(20); //浮点数的输出格式

