#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937_64 gen(time(0));
const ll mod=1e9+7;

struct T{ll x,y;};

T mul_two(T a,T b,ll p,ll w){
    T ans;
    ans.x=(a.x*b.x%p+a.y*b.y%p*w%p)%p;
    ans.y=(a.x*b.y%p+a.y*b.x%p)%p;
    return ans;
}
 
T qpow_two(T a,ll n,ll p,ll w){
    T ans{1,0};
    while(n){
        if(n&1) ans=mul_two(ans,a,p,w);
        n>>=1;
        a=mul_two(a,a,p,w);
    }
    return ans;
}
 
ll qpow(ll a,ll n,ll p){
    ll ans=1;a%=p;
    while(n){
        if(n&1) ans=ans*a%p;
        n>>=1;
        a=a*a%p;
    }
    return ans%p;
}
 
ll Legendre(ll a,ll p){
    return qpow(a,(p-1)>>1,p);
}
 
int solve(ll n,ll p){ //求x^2=n(% p)的一个解，返回-1表示无解 其中p必须是质数,返回的值是其中一个解，另一个解p-a;传入的参数需要保证n<p
    if (n==0) return 0;
    if (n==1) return 1;
    if(Legendre(n,p)+1==p) return -1;
    ll a,t,w;
    while(1){
        a=gen()%p;
        t=a*a-n;
        w=(t%p+p)%p;
        if(Legendre(w,p)+1==p) break;
    }
    T tmp{a,1};
    T ans=qpow_two(tmp,(p+1)>>1,p,w);
    return ans.x;
}
long long b,c;
int main()
{
    while(t--) {
        scanf("%lld %lld",&b,&c);
        int a=solve(((b*b-4*c)%mod+mod)%mod,mod);
        if(a==-1) printf("-1 -1\n");
        else {
            long long x=(a+b)*inv2%mod;
            long long y=(b-a+mod)*inv2%mod;
            if(x>y) swap(x,y);
            printf("%lld %lld\n",x,y);
        }
    }
}