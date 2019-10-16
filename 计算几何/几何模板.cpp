#include<bits/stdc++.h>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<cassert>

using namespace std;
const double eps=1e-8;
const int maxn=20005;
#define inf 0x3f3f3f3f3f3f3f3f
#define pi acos(-1.0)

//
int sgn(double k) {return k<-eps?-1:(k<eps?0:1);}
double Acos(double a) {return a>=1?0:(a<=-1?pi:acos(a));}
double Sqrt(double a) {return sgn(a)<=0?0:sqrt(a);}

void print(double a) //数值a保留5位四舍五入输出,
{
    char buffer[1000];
    sprintf(buffer+1,"%.10lf",a);  //
    int len=strlen(buffer+1);
    bool ok=false;
    for(int i=1;i<=len;i++) if(!(buffer[i]=='.'||buffer[i]=='0'||buffer[i]=='-')) {ok=true;break;}
    if(ok) printf("%s",buffer+1);
    else printf("%.10lf",0.0);    //
}


typedef struct point{  //点结构体
    double x,y;
    point(double a=0,double b=0) {x=a;y=b;} 
    point operator+(point other) {return point(x+other.x,y+other.y);}
    point operator-(point other) {return point(x-other.x,y-other.y);}
    point operator*(double k)    {return point(x*k,y*k);}
    point operator/(double k)    {return point(x/k,y/k);} 
    //点乘，即数量积，内积(ABcos<A,B>)
    double operator*(point other) {return x*other.x+y*other.y;}
    //叉乘，即向量积，外积(ABsin<A,B>)
    double operator^(point other) {return x*other.y-y*other.x;}
    friend bool operator<(const point &p1,const point &p2) {
        if(sgn(p1.x-p2.x)==0) return p1.y<p2.y;
        return p1.x<p2.x;
    }
    static bool compare_x(const point &p1,const point &p2) {return p1.x<p2.x;}
    static bool compare_y(const point &p1,const point &p2) {return p1.y<p2.y;}
    friend bool operator==(const point &p1,const point &p2) {
        return sgn(p1.x-p2.x)==0&&sgn(p1.y-p2.y)==0;
    }
    friend bool operator!=(const point &p1,const point &p2) {
        return sgn(p1.x-p2.x)!=0||sgn(p1.y-p2.y)!=0;
    }

    //o-p长度
    friend double len(point p) {return Sqrt(p.x*p.x+p.y*p.y);}
    friend double len2(point p) {return p.x*p.x+p.y*p.y;}
    //op与x轴夹角，范围[-pi,pi]
    friend double angle(point p) {return atan2(p.y,p.x);}    
    //判断点和有向直线的关系: -1:直线s-e方向左侧 0:直线上 1:直线右侧
    friend int point_to_line(point p,point s,point e) {return -sgn((e-s)^(p-s));}
    //op1-op2无方向角度，即与原点连线夹脚，返回值的范围[0,pi]
    friend double angle(point p1,point p2) {return Acos((p1*p2)/len(p1)/len(p2));}
    //op1-op2逆时针有向角度，返回值的范围[0,2*pi]，注意保证p1,p2不为0向量
    /*friend double angle(point p1,point p2) {
       if(point_to_line(p2,point(0,0),p1)<=0) return Acos( (p1*p2)/len(p1)/len(p2) );
       else return 2*pi-Acos( (p1*p2)/len(p1)/len(p2) );
    }*/

    //将向量p长度变为len返回一个新的向量，方向不变
    friend point extend(point p,double l) { 
        if(sgn(len(p))==0) return point(0,l);  //0向量
        return point(p*(l/len(p)));
    }

    //点p2绕着点p1顺时针方向旋转a角度，a为弧度,返回新的point
    friend point rotate(point p1,point p2,double a) {
        point vec=p2-p1;
        double xx=vec.x*cos(a)+vec.y*sin(a);
        double yy=vec.y*cos(a)-vec.x*sin(a);
        return point(p1.x+xx,p1.y+yy);
    }
    //三角形面积
    friend double area(point p1,point p2,point p3) {return fabs(((p2-p1)^(p3-p1))/2);}

    //判断点p是否在三角形abc内
    friend bool point_in_triangle(point p,point a,point b,point c) {
        return sgn(area(p,a,b)+area(p,b,c)+area(p,c,a)-area(a,b,c))==0;
    }
    //判断op是不是夹在oa->ob之间
    friend bool zhongjian(point p,point a,point o,point b) {
        double k1=angle(b-o,p-o);
        double k2=angle(b-o,a-o);
        return sgn(k1)>0&&sgn(k1-k2)<0;
    }
    //数组a需要按x排序，调用函数closest_pair
    friend double min_dis(point *a,int n){
        if(n<=1) return inf;
        int m=n/2;double x=a[m].x;
        double res=min(min_dis(a,m),min_dis(a+m,n-m));
        inplace_merge(a+1,a+m+1,a+n+1,point::compare_y);  //将[1,m]及[m+1,n]按y归并
        //sort(a+1,a+n+1,point::compare_y);

        vector<point> cur;
        for(int i=1;i<=n;i++) {
            if(fabs(a[i].x-x)>=res) continue;

            for(int j=cur.size()-1;j>=0;j--) {
                double dx=a[i].x-cur[j].x,dy=a[i].y-cur[j].y;
                if(dy>=res) break;
                res=min(res,Sqrt(dx*dx+dy*dy));
            }
            cur.push_back(a[i]);
        }
        return res;
    }

    //求最近点对「平面分治」
    //下标从1开始
    //需要compare_x,compare_y,min_dis函数
    friend double closest_pair(point *a,int n)
    {
        sort(a+1,a+n+1,point::compare_x);
        return min_dis(a,n);
    }
    void input() {scanf("%lf %lf",&x,&y);}
    void output() {printf("x:%.3lf y:%.3lf\n",x,y);}
}Vector;

/*
极角排序
bool cmp(point a,point b)
{
    return atan2(a.y,a.x)<atan2(b.y,b.x);
}
bool cmp(point a,point b)
{
    return sgn((a-point(0,0))^(b-point(0,0)))>=0;
}

*/

//求线段交点个数时用
struct endpoint{
    point p;
    int seg,st;
    endpoint(){}
    endpoint(point p,int seg,int st):p(p),seg(seg),st(st){}
    bool operator < (const endpoint &ep)const{
        if(p.y==ep.p.y){
            return st<ep.st;//y相同时，按照下断点，左端点，右端点，上端点的顺序排列
        }else{
            return p.y<ep.p.y;
        }
    }
}ep[2*maxn];

struct line{
    point s,e;
    line(point a,point b) {s=a;e=b;}
    line(double a=0,double b=0,double c=0,double d=0) {s=point(a,b);e=point(c,d);}
    //半平面交所用极角排序函数
    static bool compare_half_plane(line a,line b){
        double A=angle(a.e-a.s),B=angle(b.e-b.s);
        if(sgn(A-B)!=0) return A<B;
        return sgn((a.e-a.s)^(b.e-a.s))>0;
    }
    //计算直线p1-p2是否与直线q1-q2的交点，注意不能平行
    /*需要重载point*double  */
    friend point intersect(line l1,line l2) {
        double k=((l2.e-l2.s)^(l2.s-l1.s))/((l2.e-l2.s)^(l1.e-l1.s));
        return l1.s+(l1.e-l1.s)*k;
    }
    //返回直线倾斜角  0<=angle<=pi
    friend double angle(line p) {
        double k=atan2(p.e.y-p.s.y,p.e.x-p.s.x);
        if(sgn(k)==0) k+=pi;
        if(sgn(k-pi)==0) k-=pi;
        return k;
    }

    //两条直线平行或重合
    friend  bool parallel(line l1,line l2) {
        return sgn((l1.e-l1.s)^(l2.e-l2.s))==0;
    }

    //判断点是否在线段上
    friend bool onseg(point p,line l) {
        return sgn((l.s-p)^(l.e-p))==0&&sgn((l.s-p)*(l.e-p))<=0;
    } 
    //判断点和有向直线的关系: -1:直线s-e方向左侧 0:直线上 1:直线右侧
    friend int point_to_line(point p,line l) {
        return -sgn((l.e-l.s)^(p-l.s));
    }
    friend bool onright(point p,line l) {
        return ((l.e-l.s)^(p-l.s))<=0;
    }
    //线段与线段关系: 0:平行没有交点 1:平行有交点 2:不平行没有交点 3:不平行有交点
    friend int seg_to_seg(line l1,line l2) {
        if(sgn((l1.e-l1.s)^(l2.e-l2.s))==0) {
            if(onseg(l1.s,l2)||onseg(l1.e,l2)||onseg(l2.s,l1)||onseg(l2.e,l1)) return 1;
            else return 0;
        }
        point inter=intersect(l1,l2);
        if(onseg(inter,l1)&&onseg(inter,l2)) return 3;
        return 2;
    }

    //两直线关系: 0:平行 1:重合 2：相交
    friend int line_to_line(line l1,line l2) {
        if(parallel(l1,l2)) return point_to_line(l1.s,l2)==0;
        return 2;
    }
    //点a到直线l的距离
    friend double dis_point_line(point p,line l) { 
        if(onseg(p,l)) return 0;
        double cos0=(p-l.s)*(l.e-l.s)/(len(p-l.s)*len(l.e-l.s));
        return len(p-l.s)*sin(Acos(cos0));
    }
    //点到线段l的距离
    friend double dis_point_seg(point p,line l) {
        if(sgn((p-l.s)*(l.e-l.s))<0||sgn((p-l.e)*(l.s-l.e))<0) return min(len(p-l.s),len(p-l.e));
        return dis_point_line(p,l);
    }
    //线段到线段距离
    friend double dis_seg_seg(line l1,line l2) {
        if(seg_to_seg(l1,l2)==1||seg_to_seg(l1,l2)==3) return 0;
        return min(dis_point_seg(l1.s,l2),min(dis_point_seg(l1.e,l2),min(dis_point_seg(l2.s,l1),dis_point_seg(l2.e,l1))));
    }

    //返回点a在直线l上的垂足
    friend point chuizu(point p,line l) {
        return l.s+((l.e-l.s)*((l.e-l.s)*(p-l.s)))/len2(l.e-l.s);
    } 
    //点a关于l的对称点
    friend point duichen(point p,line l) {
        point q=chuizu(p,l);
        return point(2*q.x-p.x,2*q.y-p.y);
    }
    //求n条线段的交点个数 
    friend int manhattanIntersection(line *s,int n)
    {
        for(int i=1,k=0;i<=n;i++){
            if(s[i].s.y==s[i].e.y){
                if(s[i].s.x>s[i].e.x){
                    swap(s[i].s,s[i].e);
                }
            }else if(s[i].s.y>s[i].e.y){
                swap(s[i].s,s[i].e);
            }
            if(s[i].s.y==s[i].e.y){
                ep[k++]=endpoint(s[i].s,i,1);
                ep[k++]=endpoint(s[i].e,i,2);
            }else{
                ep[k++]=endpoint(s[i].s,i,0);
                ep[k++]=endpoint(s[i].e,i,3);
            }
        }
        sort(ep,ep+(2*n));
        set<int>bt;
        bt.insert(1000000001);
        int cnt=0;
        for(int i=0;i<2*n;i++){
            if(ep[i].st==3){
                bt.erase(ep[i].p.x);
            }else if(ep[i].st==0){
                bt.insert(ep[i].p.x);
            }else if(ep[i].st==1){
                set<int>::iterator b=bt.lower_bound(s[ep[i].seg].s.x);
                set<int>::iterator e=bt.upper_bound(s[ep[i].seg].e.x);
                cnt+=distance(b,e);
            }
        }
        return cnt;
    }
    void input() {
        scanf("%lf %lf %lf %lf",&s.x,&s.y,&e.x,&e.y);
    }
    void output() {
        printf("x1=%.2lf y1=%.2lf x2=%.2lf y2=%.2lf\n",s.x,s.y,e.x,e.y);
    }
};

struct convex_hull{
    //求点集ps的凸包，n为数组元素个数，数组下标从1开始
    //返回凸包的顶点集合
    point p[2*maxn];
    int tot;
    convex_hull(point *ps,int n)
    {
        sort(ps+1,ps+n+1);tot=0;  //凸包的顶点数
        for(int i=1;i<=n;i++) {
            while(tot>1&&((p[tot]-p[tot-1])^(ps[i]-p[tot]))<0) tot--;  //<=改成<表示保留凸包边上的其他点
            p[++tot]=ps[i];
        }

        for(int i=n-1,t=tot;i>=1;i--) {
            while(tot>t&&((p[tot]-p[tot-1])^(ps[i]-p[tot]))<0) tot--; //此处也改
            p[++tot] =ps[i];
        } 
        tot--;
    }
    //凸包面积
    double convex_hull_area()
    {
        double ans=0;
        for(int i=2;i+1<=tot;i++) ans+=area(p[1],p[i],p[i+1]);
        return ans;
    }
    //凸包长度
    double convex_hull_len() 
    {
        if(tot==0) return 0;
        double ans=0;
        for(int i=1;i<=tot;i++) ans+=len(p[i]-p[i%tot+1]);
        return ans;
    }

    //旋转卡壳求最远点对距离
    double max_dis()  
    {
        int i=1,j=1;
        if(tot==2) return len(p[0]-p[1]);
        for(int k=1;k<=tot;k++) {
            if(p[j]<p[k]) j=k;
            if(!(p[i]<p[k])) i=k;
        }
        double res=0;int si=i,sj=j;
        while(i!=sj||j!=si) {
            res=max(res,len(p[i]-p[j]));
            if((p[i%tot+1]-p[i])^(p[j%tot+1]-p[j])<0) i=i%tot+1;
            else j=j%tot+1;
        }
        return res;
    }
     //判断点p是否在凸包a内
    friend bool point_in_convex_hull(point p,convex_hull a) {
        int l=2,r=a.tot-1;
        while(l<=r) {
            int mid=(l+r)>>1;
            double k1=(a.p[mid]-a.p[1])^(p-a.p[1]),k2=(a.p[mid+1]-a.p[1])^(p-a.p[1]);
            if(k1>=0&&k2<=0) {
                if(((a.p[mid+1]-a.p[mid])^(p-a.p[mid]))>=0) return true;
                return false;
            }
            if(k1<0) r=mid-1;
            else l=mid+1;
        }
        return false;
    }
    //判断凸包是否相交
    friend bool convex_hull_intersect(convex_hull a,convex_hull b) {
        int n=a.tot,m=b.tot;
        for(int i=1;i<=n;i++) if(point_in_convex_hull(a.p[i],b)) return true;
        for(int i=1;i<=m;i++) if(point_in_convex_hull(b.p[i],a)) return true;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) {
            int k=seg_to_seg(line(a.p[i],a.p[i%n+1]),line(b.p[j],b.p[j%m+1]));
            if(k==1||k==3) return true;
        }
        return false;
    }
};

//半平面交结构体，初始化必须提供线集，线集必须逆时针，点集s-e左侧为半平面
struct half_plane_intersect{
    line que[maxn];       //存储构成半平面交的直线几何，起始位置head,终止位置tail
    int head,tail,tot;  //head,tail表示半平面交在数组que中的起始及终止位置,tot为临时变量
    point p[maxn];        //求半平面交的面积
    int k;                //表示半平面交有k个顶点
    
    half_plane_intersect(line *L,int n){
        head=1,tail=0,tot=0;
        sort(L+1,L+n+1,line::compare_half_plane);
        
        for(int i=1;i<n;i++) {
            if(sgn(angle(L[i+1].e-L[i+1].s)-angle(L[i].e-L[i].s))==0) continue;
            L[++tot]=L[i];
        }
        L[++tot]=L[n];

        for(int i=1;i<=tot;i++) {
            while(tail-head>=1&& onright(intersect(que[tail],que[tail-1]),L[i])) tail--;
            while(tail-head>=1&& onright(intersect(que[head],que[head+1]),L[i])) head++;
            que[++tail]=L[i];
        }

        //处理尾部和头部是否可能影响半平面交
        while(tail-head>=1&& onright(intersect(que[head],que[head+1]),que[tail])) head++;
        while(tail-head>=1&& onright(intersect(que[tail],que[tail-1]),que[head])) tail--;     
    }
    //求出半平面交的顶点
    void get_intersect(){
        k=0;
        for(int i=head;i<tail;i++) p[++k]=intersect(que[i],que[i+1]);
        p[++k]=intersect(que[tail],que[head]);
    }

    //求半平面交的面积
    //注意这里面积为无穷大的情况也会返回0
    double half_plane_area() {
        get_intersect();
        double ans=0;
        for(int i=2;i+1<=k;i++) ans+=area(p[1],p[i],p[i+1]);
        return ans;
    }
};


struct circle{
    point o;
    double r;
    circle(point a,double b) {o=a;r=b;}
    circle(double a=0,double b=0,double c=0) {o.x=a,o.y=b,r=c;}
    bool operator==(circle c) {return o==c.o&&sgn(r-c.r)==0;}
    double area() {return pi*r*r;}
    //求三角形外接圆
    circle(point a,point b,point c) {
        point p1=rotate((a+b)/2,b,3*pi/2),p2=rotate((b+c)/2,c,3*pi/2);
        o=intersect(line((a+b)/2,p1),line((b+c)/2,p2));
        r=len(o-a);
    }

    //求三角形内切圆，nouse无实际作用，只是用来区别上面外接圆
    circle(point a,point b,point c,int nouse){
        if(sgn((b-a)^(c-b))<0) swap(b,c);
        point p1=rotate(a,b,2*pi-(angle(c-a,b-a)/2)),p2=rotate(b,c,2*pi-(angle(a-b,c-b)/2));
        o=intersect(line(a,p1),line(b,p2));
        r=dis_point_line(o,line(b,c));
    }

    //点和圆的关系:0:圆内 1:圆上 2:圆外
    friend int point_to_circle(point p,circle c) {return 1+sgn(len(p-c.o)-c.r);}
    //直线和圆的关系:0:与圆相交 1:圆上 2:圆外
    friend int line_to_circle(line l,circle c) {return 1+sgn(dis_point_line(c.o,l)-c.r);}
    //线段和圆的关系:0:圆内或者与圆相交 1:有一个端点在圆上 2:圆外
    friend int seg_to_circle(line l,circle c)  {return 1+sgn(dis_point_seg(c.o,l)-c.r);}

    //圆c1与圆c2的关系:0:内含 1:内切 2:相交 3:外切 4:相离
    friend int circle_to_circle(circle c1,circle c2) {
        double d=len(c1.o-c2.o);
        if(sgn(d-c1.r-c2.r)>0) return 4;
        if(sgn(d-c1.r-c2.r)==0) return 3;
        if(c1.r<c2.r) swap(c1,c2);
        if(sgn(c1.r-c2.r-d)<0) return 2;
        if(sgn(c1.r-c2.r-d)==0) return 1;
        return 0;
    }

    //返回直线与圆交点个数，交点坐标存在引用p1,p2中
    friend int line_circle_cross(line l,circle c,point &p1,point &p2) {
        if(line_to_circle(l,c)==2) return 0;
        double d=dis_point_line(c.o,l);
        point p=chuizu(c.o,l);
        d=Sqrt(c.r*c.r-d*d);
        if(sgn(d)==0) {
            p1=p2=p;
            return 1;
        }
        p1=p+extend(l.e-l.s,d);p2=p+extend(l.e-l.s,-d);
        return 2;
    }

    //返回两个圆交点个数，交点坐标存在引用p1,p2中
    friend int circle_circle_cross(circle c1,circle c2,point &p1,point &p2) {
        int relation=circle_to_circle(c1,c2);
        if(relation==0||relation==4) return 0;
        double d=len(c1.o-c2.o);
        if(c1.r>c2.r) swap(c1,c2);
        double k=Acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*d*c1.r));
        p1=c1.o+extend(rotate(c1.o,c2.o,2*pi-k)-c1.o,c1.r);
        p2=c1.o+extend(rotate(c1.o,c2.o,k)-c1.o,c1.r);
        if(sgn(d-c1.r-c2.r)==0||sgn(c2.r-d-c1.r)==0) return 1;
        return 2;
    }

    //两个圆相交部分面积
    friend double circle_circle_area(circle c1,circle c2) {
        int k=circle_to_circle(c1,c2);
        if(k>=3) return 0;
        if(k<=1) return min(c1.area(),c2.area());
        double d=len(c1.o-c2.o),hf=(c1.r+c2.r+d)/2;
        double ss=2*Sqrt(hf*(hf-c1.r)*(hf-c2.r)*(hf-d));
        double a1=acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
        a1=a1*c1.r*c1.r;
        double a2=acos((c2.r*c2.r+d*d-c1.r*c1.r)/(2.0*c2.r*d));
        a2=a2*c2.r*c2.r;
        return a1+a2-ss;
    }

    //返回三角形oab与圆相交的面积
    friend double circle_triangle_area(circle c,point a,point b) {
        if(sgn((a-c.o)^(b-c.o))==0) return 0.0;
        point q[5],p1,p2;int len=0;q[len++]=a;line l=line(a,b);
        if(line_circle_cross(l,c,q[1],q[2])==2) {
            if(sgn((a-q[1])*(b-q[1]))<0) q[len++]=q[1];
            if(sgn((a-q[2])*(b-q[2]))<0) q[len++]=q[2];
        }
        q[len++]=b;double res=0;
        if(len==4&&sgn((q[0]-q[1])*(q[2]-q[1]))>0) swap(q[1],q[2]);
        for(int i=0;i<len-1;i++) {
            if(point_to_circle(q[i],c)==2||point_to_circle(q[i+1],c)==2) {
                double ang=angle(q[i]-c.o,q[i+1]-c.o);
                res+=c.r*c.r*ang/2;
            }else res+=fabs((q[i]-c.o)^(q[i+1]-c.o))/2.0;
        }
        return res;
    }

    //求最小圆覆盖
    static circle min_cover_circle(point *p,int n){
        random_shuffle(p+1,p+1+n);
        circle ans(p[1],0);
        for(int i=1;i<=n;++i) if(sgn(len(p[i]-ans.o)-ans.r)>0){
            ans=circle(p[i],0);
            for(int j=1;j<i;j++) if(sgn(len(p[j]-ans.o)-ans.r)>0){
                ans=circle(point((p[i].x+p[j].x)/2.0,(p[i].y+p[j].y)/2.0),len(p[i]-p[j])/2.0);
                for(int k=1;k<j;++k) if(sgn(len(p[k]-ans.o)-ans.r)>0){
                    ans=circle(p[i],p[j],p[k]); //外接圆
                }
            }
        }
        return ans;
    } 

    void input() {
        scanf("%lf %lf %lf",&o.x,&o.y,&r);
    }
    void output() {
        printf("x= %.2lf y= %.2lf r=%.2lf\n",o.x,o.y,r);
    }

};

/*多边形
1. p,l数组的下表范围是[1,n]
*/
struct polygon{
    int n;
    point p[maxn];
    line l[maxn];
    //获得所有边，存储在l中
    void getline() {for(int i=1;i<=n;i++) l[i]=line(p[i],p[i%n+1]);}
    //获得跑p中点的方向，0表示顺时针，1表示逆时针
    friend bool get_dir(polygon &a) {
        double sum=0;
        for(int i=1;i<=a.n;i++) sum+=(a.p[i]^a.p[i%a.n+1]);
        return sgn(sum)>0;   
    }
    //判断点和任意多边形关系0:内部 1:点上 2:边上 3:外部
    friend int point_to_polygon(point p,polygon & a) {
        for(int i=1;i<=a.n;i++) if(a.p[i]==p) return 1;
        a.getline();
        for(int i=1;i<=a.n;i++) if(onseg(p,a.l[i])) return 2;
        int cnt=0;
        for(int i=1;i<=a.n;i++) {
            int j=i%a.n+1,k=sgn((p-a.p[j])^(a.p[i]-a.p[j]));
            int u=sgn(a.p[i].y-p.y),v=sgn(a.p[j].y-p.y);
            if(k>0 && u<0 && v>=0) cnt++;
            if(k<0 && v<0 && u>=0) cnt--;
        }
        return cnt!=0?0:3;
    }
    //多边形面积
    double area() {
        double ans=0;
        for(int i=1;i<=n;i++) ans+=(p[i]^p[i%n+1]);
        return fabs(ans/2);
    }

    //求简单多边形与圆相交的面积
    friend double polygon_circle_area(polygon &pol,circle c) {
        double ans=0;
        for(int i=1;i<=pol.n;i++) {
            int j=i%pol.n+1;
            if(sgn((pol.p[j]-c.o)^(pol.p[i]-c.o))>=0) ans+=circle_triangle_area(c,pol.p[i],pol.p[j]);
            else ans-=circle_triangle_area(c,pol.p[i],pol.p[j]);
        }
        return fabs(ans);
    }

    //判断点和任意多边形的关系(O(n))
    /*0:外部 1:内部 2:边上 3:点上*/
    friend int relation(polygon &a,point p) {
        for(int i=1;i<=a.n;i++) if(a.p[i]==p) return 3;
        for(int i=1;i<=a.n;i++) if(onseg(p,line(a.p[i],a.p[i%a.n+1]))) return 2;
        int res=0;
        for(int i=1;i<=a.n;i++) {
            int j=i%a.n+1;
            int k=sgn((p-a.p[j])^(a.p[i]-a.p[j]));
            int u=sgn(a.p[i].y-p.y);
            int v=sgn(a.p[j].y-p.y);
            if(k>0&&u<0&&v>=0) res++;
            if(k<0&&v<0&&u>=0) res--;
        }    
        return res!=0;
    }

    void input() {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%lf %lf",&p[i].x,&p[i].y);
    }
    void output() {
        printf("n=%d\n",n);
        for(int i=1;i<=n;i++) printf("%lf %lf\n",p[i].x,p[i].y);
    }
};

int main()
{

}