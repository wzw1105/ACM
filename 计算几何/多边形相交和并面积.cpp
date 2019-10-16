/* 
    类型：多边形相交面积模板 
*/  
  
#include<cstdio>  
#include<iostream>  
#include<algorithm>  
#include<cstring>  
#include<cmath>  
using namespace std;  
#define maxn 510  
const double eps=1E-8;  
int sig(double d){  
    return(d>eps)-(d<-eps);  
}  
struct Point{  
    double x,y; Point(){}  
    Point(double x,double y):x(x),y(y){}  
    bool operator==(const Point&p)const{  
        return sig(x-p.x)==0&&sig(y-p.y)==0;  
    }  
};  
double cross(Point o,Point a,Point b){  
    return(a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);  
}  
double area(Point* ps,int n){  
    ps[n]=ps[0];  
    double res=0;  
    for(int i=0;i<n;i++){  
        res+=ps[i].x*ps[i+1].y-ps[i].y*ps[i+1].x;  
    }  
    return res/2.0;  
}  
int lineCross(Point a,Point b,Point c,Point d,Point&p){  
    double s1,s2;  
    s1=cross(a,b,c);  
    s2=cross(a,b,d);  
    if(sig(s1)==0&&sig(s2)==0) return 2;  
    if(sig(s2-s1)==0) return 0;  
    p.x=(c.x*s2-d.x*s1)/(s2-s1);  
    p.y=(c.y*s2-d.y*s1)/(s2-s1);  
    return 1;  
}  
//多边形切割  
//用直线ab切割多边形p，切割后的在向量(a,b)的左侧，并原地保存切割结果  
//如果退化为一个点，也会返回去,此时n为1  
void polygon_cut(Point*p,int&n,Point a,Point b){  
    static Point pp[maxn];  
    int m=0;p[n]=p[0];  
    for(int i=0;i<n;i++){  
        if(sig(cross(a,b,p[i]))>0) pp[m++]=p[i];  
        if(sig(cross(a,b,p[i]))!=sig(cross(a,b,p[i+1])))  
            lineCross(a,b,p[i],p[i+1],pp[m++]);  
    }  
    n=0;  
    for(int i=0;i<m;i++)  
        if(!i||!(pp[i]==pp[i-1]))  
            p[n++]=pp[i];  
    while(n>1&&p[n-1]==p[0])n--;  
}  
//---------------华丽的分隔线-----------------//  
//返回三角形oab和三角形ocd的有向交面积,o是原点//  
double intersectArea(Point a,Point b,Point c,Point d){  
    Point o(0,0);  
    int s1=sig(cross(o,a,b));  
    int s2=sig(cross(o,c,d));  
    if(s1==0||s2==0)return 0.0;//退化，面积为0  
    if(s1==-1) swap(a,b);  
    if(s2==-1) swap(c,d);  
    Point p[10]={o,a,b};  
    int n=3;  
    polygon_cut(p,n,o,c);  
    polygon_cut(p,n,c,d);  
    polygon_cut(p,n,d,o);  
    double res=fabs(area(p,n));  
    if(s1*s2==-1) res=-res;return res;  
}  
//求两多边形的交面积  
double intersectArea(Point *p1,int n,Point *p2,int m){  
    if(area(p1,n)<0) reverse(p1,p1+n);  
    if(area(p2,m)<0) reverse(p2,p2+m);  
    p1[n]=p1[0];  
    p2[m]=p2[0];  
    double res=0;  
    for(int i=0;i<n;i++){  
        for(int j=0;j<m;j++){  
            res+=intersectArea(p1[i],p1[i+1],p2[j],p2[j+1]);  
        }  
    }  
    return res;//assumeresispositive!  
}  
//求两多边形的并面积
double andArea(Point *p1,int n,Point *p2,int m) {
    return fabs(area(p1,n))+fabs(area(p2,m))-intersectArea(p1,n,p2,m);
}
//hdu-3060求两个任意简单多边形的并面积  
Point p1[maxn],p2[maxn];  
int n,m;  
int main(){  
    while(scanf("%d%d",&n,&m)!=EOF){  
        for(int i=0;i<n;i++) scanf("%lf%lf",&p1[i].x,&p1[i].y);  
        for(int i=0;i<m;i++) scanf("%lf%lf",&p2[i].x,&p2[i].y);  
        double ans= andArea(p1,n,p2,m);  //intersectArea(p1,n,p2,m)
        printf("%.2f\n",ans);  
    }  
    return 0;  
}