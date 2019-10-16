#include<bits/stdc++.h>

using namespace std;
const int maxn=3e6+10;

#define bg1(x) cout<<(#x)<<":"<<(x)<<" "<<endl
#define bg2(x,y) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<endl
#define bg3(x,y,z) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<endl
#define bg4(x,y,z,w) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<endl
#define bg5(x,y,z,w,k) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<(#k)<<":"<<(k)<<" "<<endl
#define bg6(x,y,z,w,k,l) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<(#k)<<":"<<(k)<<" "<<(#l)<<":"<<(l)<<" " <<endl

int n,a[maxn],sta[maxn],tot,minl[maxn],minr[maxn],maxl[maxn],maxr[maxn];

void solve_min_l(){  //左边第一个比当前位严格小的数位置
    tot=0;
    for(int i=n;i>=1;i--) {
        while(tot&&a[i]<a[sta[tot]]) {minl[sta[tot]]=i;tot--;}
        sta[++tot]=i;
    }
    while(tot) {minl[sta[tot]]=0;tot--;}
}

void solve_min_r(){  //右边第一个比当前位严格小的数位置
    tot=0;
    for(int i=1;i<=n;i++) {
        while(tot&&a[i]<a[sta[tot]]) {minr[sta[tot]]=i;tot--;}
        sta[++tot]=i;
    }
    while(tot) {minr[sta[tot]]=n+1;tot--;}
}

void solve_max_l(){  //左边第一个比当前位严格大的数位置
    tot=0;
    for(int i=n;i>=1;i--) {
        while(tot&&a[i]>a[sta[tot]]) {maxl[sta[tot]]=i;tot--;}
        sta[++tot]=a[i];
    }
    while(tot) {maxl[sta[tot]]=0;tot--;}
}

void solve_max_r(){  //右边第一个比当前位严格大的数位置
    tot=0;
    for(int i=1;i<=n;i++) {
        while(tot&&a[i]>a[sta[tot]]) {maxr[sta[tot]]=i;tot--;}
        sta[++tot]=i;
    }
    while(tot) {maxr[sta[tot]]=n+1;tot--;}
}

int main()
{
    //freopen("/Users/wzw/Desktop/ACM/1.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    solve_min_l();
    solve_min_r();
    solve_max_l();
    solve_max_r();

    for(int i=1;i<=n;i++) bg5(i,minl[i],minr[i],maxl[i],maxr[i]);
}