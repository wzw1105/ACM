#include<bits/stdc++.h>

using namespace std;
#define inf 0x3f3f3f3f

int gcd(int a,int b)
{
    return (b==0?a:gcd(b,a%b));
}

//分母大于零，分子可小于零
struct fenshu{
    int x,y;
    fenshu(int a=0,int b=1) {
        x=a;y=b;
    }

    fenshu operator+(fenshu b) {
        int _gcd=gcd(y,b.y);
        fenshu res=fenshu(abs(x*(b.y/_gcd)+b.x*(y/_gcd)),abs(y*(b.y/_gcd)));
        int gcd_=abs(gcd(res.x,res.y));
        res.x/=gcd_;res.y/=gcd_;
        if(b.y*x+y*b.x<0) res.x=-res.x;
        return res;
    }

    fenshu operator-(fenshu b) {
        int _gcd=gcd(y,b.y);
        fenshu res=fenshu(abs(x*(b.y/_gcd)-b.x*(y/_gcd)),abs(y*(b.y/_gcd)));
        int gcd_=gcd(res.x,res.y);
        res.x/=gcd_;res.y/=gcd_;
        if(b.y*x-y*b.x<0) res.x=-res.x;
        return res;
    }

    fenshu operator*(fenshu b) {
        fenshu res=fenshu(x*b.x,y*b.y);
        int _gcd=gcd(abs(res.x),abs(res.y));
        res.x/=_gcd;res.y/=_gcd;
        return res;
    }

    fenshu operator/(fenshu b) {
        if(b.y==0) {
            printf("error\n");
            return fenshu(inf,inf);
        }
        fenshu res=fenshu(x*b.y,y*b.x);
        if(res.y<0) {
            res.x=-res.x;
            res.y=-res.y;
        }
        int _gcd=gcd(abs(res.x),abs(res.y));
        res.x/=_gcd;res.y/=_gcd;
        return res;
    }
    friend double trans(fenshu a) {  //转化成double
        return 1.0*a.x/a.y;
    }
    friend bool operator<(const fenshu &a,const fenshu &b){
        if(a.x*b.x<0) return a.x<b.x;
        int _gcd=gcd(a.y,b.y);
        return a.x*(b.y/_gcd)<b.x*(a.y/_gcd);
    }
    friend bool operator>(const fenshu &a,const fenshu &b) {
        if(a.x*b.x<0) return a.x>b.x;
        int _gcd=gcd(a.y,b.y);
        return a.x*(b.y/_gcd)>b.x*(a.y/_gcd);
    }
    friend bool operator==(const fenshu &a,const fenshu &b) {
        return a.x==b.x&&a.y==b.y;
    }
    friend bool operator>=(const fenshu &a,const fenshu &b) {
        return a>b||a==b;
    }
    friend bool operator<=(const fenshu&a,const fenshu &b) {
        return a<b||a==b;
    }
    void print() {
        printf("%d/%d\n",x,y);
    }
};


int main()
{
    int a,b,c,d;
    while(~scanf("%d %d %d %d",&a,&b,&c,&d)) {
        fenshu m=fenshu(a,b);
        fenshu n=fenshu(c,d);

        fenshu jia=m+n;
        jia.print();

        fenshu jian=m-n;
        jian.print();

        fenshu chen=m*n;
        chen.print();

        fenshu chu=m/n;
        chu.print();

        if(m>n)  printf("a>b\n");
        else if(m==n) printf("a==b\n");
        else printf("a<b\n");
    }
}