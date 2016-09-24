const double eps = 1e-8;
const int N = 10040;
const int M = 2400020;
const int INF = 0x3f3f3f3f;
int sgn(double x)
{
    if(fabs(x)<eps)return 0;
    if(x>0)return 1;
    return -1;
}
struct point3
{
    double x,y,z;
    point3(double x=0,double y = 0, double z = 0):x(x),y(y),z(z){};
    point3 operator + (const point3 &b)const
    {
        return point3(x+b.x,y+b.y,z+b.z);
    }
    point3 operator - (const point3 &b)const
    {
        return point3(x-b.x,y-b.y,z-b.z);
    }
    point3 operator * (const double &k)const
    {
        return point3(x*k,y*k,z*k);
    }
    point3 operator == (const point3 &b)const
    {
        return sgn(x-b.x)==0 && sgn(y-b.y)==0 && sgn(z-b.z)==0;
    }
    double len()
    {
        return sqrt(x*x+y*y+z*z);
    }
    point3 adjust(double L)
    {
        double t = len();
        L/=t;
        return point3(x*L,y*L,z*L);
    }
};
typedef point3 Vector3;
double dot(point3 a,point3 b)
{
    return a.x*b.x + a.y*b.y +a.z*b.z;
}
Vector3 cross(Vector3 a,Vector3 b)
{
    return point3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
double dis_to_plane(point3 p, point3 p0, point3 n)
{
    return fabs(dot(p-p0,n))/n.len();
}
int line_plane_inter(point3 p1, point3 p2,point3 p0,point3 n,point3 &s)
{
    point3 v = p2-p1;
    double tt =dot(n,v);
    if(sgn(tt)==0)////////////////
    {
        if(sgn(dis_to_plane(p1,p0,n))==0)
            return 2;
        else
            return 0;
    }
    double t = dot(n,p0-p1)/dot(n,p2-p1);
    if(t<0 || t>1)
        return 0;
    s = p1+v*t;
    return 1;
}
struct face
{
    int a,b,c;
    bool ok;
};

struct CH3D
{
    int n;
    point3 P[N];
    int num;
    face F[8*N];
    int g[N][N];
    double vlen(point3 a)
    {
        return a.len();
    }
    double area2(point3 a, point3 b, point3 c)
    {
        return vlen(cross(b-a,c-a));
    }
    double volume6(point3 a, point3 b, point3 c, point3 d)
    {
        return dot(d-a,cross(b-a,c-a));
    }
    double dblcmp(point3 &p, face &f)
    {
        point3 m = P[f.b] - P[f.a];
        point3 n = P[f.c] - P[f.a];
        point3 t = p - P[f.a];
        double ret = dot(cross(m,n),t);
        return ret;
    }
    void deal(int p,int a,int b)
    {
        int f = g[a][b];
        face add;
        if(F[f].ok)
        {
            if(dblcmp(P[p],F[f])>eps)
                dfs(p,f);
            else{
                add.a = b;
                add.b = a;
                add.c = p;
                add.ok = 1;
                g[p][b] = g[a][p] = g[b][a] = num;
                F[num++] = add;
            }
        }
    }
    void dfs(int p,int now)
    {
        F[now].ok = 0;
        deal(p,F[now].b,F[now].a);
        deal(p,F[now].c,F[now].b);
        deal(p,F[now].a,F[now].c);
    }
    bool same(int s,int t)
    {
        point3 &a = P[F[s].a];
        point3 &b = P[F[s].b];
        point3 &c = P[F[s].c];
        return sgn(volume6(a,b,c,P[F[t].a]))==0 &&
               sgn(volume6(a,b,c,P[F[t].b]))==0 &&
               sgn(volume6(a,b,c,P[F[t].c]))==0;
    }
    void create()
    {
        face add;
        num = 0;
        if(n<4)return ;
        bool flag = 1;
        for(int i=1;i<n;i++)
        {
            if(vlen(P[0]-P[i])>eps)
            {
                swap(P[1],P[i]);
                flag = 0;
                break;
            }
        }
        if(flag)
            return;
        flag = 1;
        for(int i=2;i<n;i++)
        {
            if(vlen(cross(P[1]-P[0],P[i]-P[0]))>eps)
            {
                swap(P[2],P[i]);
                flag = 0;
                break;
            }
        }
        if(flag)
            return ;
        flag = 1;
        for(int i=3;i<n;i++)
        {
            if(fabs(volume6(P[0],P[1],P[2],P[i]))>eps)
            {
                swap(P[3],P[i]);
                flag = 0;
                break;
            }
        }
        if(flag)
            return;
        for(int i=0;i<4;i++)
        {
            add.a = (i+1)%4;
            add.b = (i+2)%4;
            add.c = (i+3)%4;
            add.ok = 1;
            if(dblcmp(P[i],add)>0)
                swap(add.b,add.c);
            g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
            F[num++] = add;
        }
        for(int i=4;i<n;i++)
        {
            for(int j=0;j<num;j++)
            {
                if(F[j].ok && dblcmp(P[i],F[j])>eps)
                {
                    dfs(i,j);
                    break;
                }
            }
        }
        int tmp = num;
        num =0;
        for(int i=0;i<tmp;i++)
        {
            if(F[i].ok)
                F[num++] = F[i];
        }
    }
    double area()
    {
        double ret = 0;
        if(n==3)
            return area2(P[0],P[1],P[2])/2.0;
        for(int i=0;i<num;i++)
            ret+=area2(P[ F[i].a ],P[ F[i].b ], P[ F[i].c ]);
        return ret/2.0;
    }
    double volume()
    {
        double ret = 0;
        point3 tmp(0,0,0);
        for(int i=0;i<num;i++)
            ret+=volume6(tmp,P[ F[i].a ],P[ F[i].b ], P[ F[i].c ]);
        return fabs(ret)/6.0;
    }
    int triangle()
    {
        return num;
    }
    int polygon()
    {
        int ret = 0, flag = 0;
        for(int i=0;i<num;i++)
        {
            flag = 1;
            for(int j=0;j<i;j++)
            {
                if(same(i,j))
                {
                    flag = 0;
                    break;
                }
            }
            ret+=flag;
        }
        return ret;
    }

    double point3_to_face(point3 p,int i)
    {
        return fabs(volume6(P[ F[i].a ], P[ F[i].b ], P[F[i].c],p)/area2(P[ F[i].a ], P[ F[i].b ], P[F[i].c]));
    }
}ch;

void change(point *p, point3 *pp, point3 t,int n)
{
    double a = t.x, b = t.y, c = t.z;
    if(sgn(a*a+b*b)==0)
    {
        for(int i=0;i<n;i++)
        {
            p[i].x = pp[i].x;
            p[i].y = pp[i].y;
        }
        return ;
    }
    for(int i=0;i<n;i++)
    {
        double cosC = b/sqrt(a*a+b*b);
        double sinC = a/sqrt(a*a+b*b);
        point3 tmp;
        tmp.x = pp[i].x * cosC - pp[i].y * sinC;
        tmp.y = pp[i].x * sinC + pp[i].y * cosC;//////////
        tmp.z = pp[i].z;
        pp[i] = tmp;
        cosC = c/sqrt(a*a + b*b +c*c);
        sinC = sqrt(a*a + b*b)/sqrt(a*a + b*b +c*c);
        tmp.x = pp[i].x;
        tmp.y = pp[i].y*cosC - pp[i].z*sinC ;
        tmp.z = pp[i].y*sinC + pp[i].z*cosC ;
        pp[i] = tmp;
        p[i].x = pp[i].x;
        p[i].y = pp[i].y;
    }
}

point3 pp[N], fp[N];
point p[N],cp[N];
int q,tot;
void check(int num, point3 a,point3 b, point3 c)
{
    if(num == 1)
        fp[tot++] = c;
    if(num == 2)
        fp[tot++] = a, fp[tot++] = b;
}
int main()
{
    int kase,kk=0;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d %d",&ch.n,&q);
        for(int i=0;i<ch.n;i++)
        {
            scanf("%lf %lf %lf",&ch.P[i].x,&ch.P[i].y,&ch.P[i].z);
            pp[i] = ch.P[i];
        }
        ch.create();
        printf("Case #%d:\n",++kk);
        while(q--)
        {
            double a,b,c,d;
            scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
            point3 p0, pn = point3(a,b,c),res;
            if(sgn(a)!=0) p0 = point3(-d/a,0,0);
            else if(sgn(b)!=0) p0 = point3(0,-d/b,0);
            else if(sgn(c)!=0) p0 = point3(0,0,-d/c);
            else p0 = point3(0,0,0);
            int ret;
            tot = 0;
            for(int i=0;i<ch.num;i++)
            {
                ret  = line_plane_inter(pp[ch.F[i].a],pp[ch.F[i].b],p0,pn,res);
                check(ret,pp[ch.F[i].a],pp[ch.F[i].b],res);

                ret  = line_plane_inter(pp[ch.F[i].a],pp[ch.F[i].c],p0,pn,res);
                check(ret,pp[ch.F[i].a],pp[ch.F[i].c],res);

                ret  = line_plane_inter(pp[ch.F[i].b],pp[ch.F[i].c],p0,pn,res);
                check(ret,pp[ch.F[i].b],pp[ch.F[i].c],res);
            }
            change(p,fp,pn,tot);
            int m = convex_hull(p,tot,cp);
            double ans = fabs(poly_area(cp,m));
            printf("%.3f\n",ans);

        }
    }
    return 0;
}