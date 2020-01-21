/*
    correctly used times = 
    used in = { 
   	
    }
*/


bool findpath(int x) {
    visx[x] = true;
    for(int y = 1 ; y <= ny ; ++y)
    {
        if(!visy[y] && lx[x] + ly[y] == weight(x,y)) //y不在交错路中且edge(x,y)必须在相等子图中
        {
            visy[y] = true;
            if(match[y] == -1 || findpath(match[y]))//如果y还为匹配或者从y的match还能另外找到一条匹配边
            {
                match[y] = x;
                return true;
            }
        }
    }
    return false;
}

void KM(){
    for(int x = 1 ; x <= nx ; ++x)
    {
        while(true)
        {
            memset(visx,false,sizeof(visx));//访问过X中的标记
            memset(visy,false,sizeof(visy));//访问过Y中的标记
            if(findpath(x))//找到了增广路，跳出继续寻找下一个
                break;
            else
            {
                for(int i = 1 ; i <= nx ; ++i)
                {
                    if(visx[i])//i在交错路中
                    {
                        for(int j = 1 ; j <= ny ; ++j)
                        {
                            if(visy[j])//j不在交错路中，对应第二类边
                                delta = Min(delta,lx[x] + ly[y] - weight(i,j))
                        }
                    }
                }
                for(int i = 1 ; i <= nx ; ++i)//增广路中xi - delta
                    if(visx[i])
                        lx[i] -= delta;
                for(int j = 1 ; j <= ny ; ++j)//增广路中yj + delta
                    if(visy[j])
                        ly[j] += delta;
            }

    }
}

// implementation from https://blog.csdn.net/sixdaycoder/article/details/47720471
    