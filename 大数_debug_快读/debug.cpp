#pragma comment(linker,"/STACK:102400000,102400000")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("O3")

#include<bits/stdc++.h>

using namespace std;
#define wzw1105

#define bg1(x) cout<<(#x)<<":"<<(x)<<" "<<endl
#define bg2(x,y) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<endl
#define bg3(x,y,z) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<endl
#define bg4(x,y,z,w) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<endl
#define bg5(x,y,z,w,k) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<(#k)<<":"<<(k)<<" "<<endl
#define bg6(x,y,z,w,k,l) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<(#k)<<":"<<(k)<<" "<<(#l)<<":"<<(l)<<" " <<endl
template<typename T>
void debug(T a[],int n){
	for(int i=1;i<=n;i++) cout << a[i] << (i==n?"\n":" ");
}

/*--------------------------------------fast read----------------------------------------------*/
template<typename T> 
inline void read(T &x) {
	x = 0;int f = 1;char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}x=x*f;
}

template<typename T>
inline void write(T x)
{
    static T buf[20],len; len=0;
    if(x<0)x=-x,putchar('-');
    for(;x;x/=10)buf[len++]=x%10;
    if(!len)putchar('0');
    else while(len)putchar(buf[--len]+'0');
}

template<typename A,typename B> inline void read(A &a, B &b){read(a); read(b);}
template<typename A,typename B,typename C> inline void read(A &a, B &b, C &c){read(a); read(b); read(c);}
template<typename A,typename B,typename C,typename D> inline void read(A&a,B&b,C&c,D&d){read(a);read(b);read(c);read(d);}
inline long long read(){long long x; read(x); return x;}
/*--------------------------------------fast read----------------------------------------------*/

template<typename T> inline bool cma(T &a,const T&b){return a<b?a=b,true:false;}
template<typename T> inline bool cmi(T &a, const T &b){return a>b?a=b,true:false;}

void debug(int *(*a),int n,int m)
{
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) printf("%d%c",a[i][j],j==m?'\n':' ');
}

/*---------------------------------------previous use-----------------------------------------*/
#define pii pair<int, int>
#define mem(a,b) memset(a,b,sizeof(a))
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,a,b) for(int i=(a);i>=(b);i--)
#define pi acos(-1.0)
#define inf 0x3f3f3f3f
#define Rand() (rand()|rand()<<15)
#define Srand() srand(time(0)^(unsigned)(unsigned long long)(new char))
#define typemax(type)   numeric_limits<type>::max()
#define typemin(type)   numeric_limits<type>::min()
typedef long long ll;

#define bg1(x) cout<<(#x)<<":"<<(x)<<" "<<endl
#define bg2(x,y) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<endl
#define bg3(x,y,z) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<endl
#define bg4(x,y,z,w) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<endl
#define bg5(x,y,z,w,k) cout<<(#x)<<":"<<(x)<<" "<<(#y)<<":"<<(y)<<" "<<(#z)<<":"<<(z)<<" "<<(#w)<<":"<<(w)<<" "<<(#k)<<":"<<(k)<<" "<<endl

template<typename T> inline void print(T x) {if(x<0)putchar('-'),x=-x;if(x>=10)print(x/10);putchar(x%10+'0');}
template<typename E> E gcd(E a,E b){return b==0?a:gcd(b,a%b);}
template<typename E> E lcm(E a,E b){return a*b/gcd(a,b);}
template<typename E> E ex_gcd(E a,E b,E &x,E&y) {if(b==0){x=1;y=0;}else {ex_gcd(b,a%b,y,x);y-=(a/b)*x;}}
template<typename E> E quick_mul(E a,E b,E c){E ans=0;while(b){if(b&1) ans=(ans+a)%c;a=(a+a)%c;b>>=1;}  return ans;}
template<typename E> E quick_pow(E a,E b,E c){E ans=1;while(b){if(b&1) ans=ans*a%c;a=a*a%c;b>>=1;}return ans;}
template<typename E> E inv1(E a,E b){return quick_pow(a,b-2,b);}
template<typename E> E inv2(E a,E b){E x,y;ex_gcd(a,b,x,y);return (x%b+b)%b;}
/*---------------------------------------previous use---------------------------------------------*/

int main()
{
	freopen("/Users/wzw/Desktop/ACM/1.in","r",stdin);
	long long n;
	read(n);
	write(n);
}

//测试时间
int main()
{
    freopen("/Users/wzw/Desktop/ACM/1.in","r",stdin);
    ofstream out("/Users/wzw/Desktop/ACM/1.out");
    clock_t start=clock(),finish;

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    finish=clock();
    printf("Time=%.2lf ms\n",(finish-start)*1000.0/CLOCKS_PER_SEC);
}


/*
debug:
1.注意多组数据，注意数组清空的大小及需要清空的位置
2.注意多组数据输出要打换行
3.注意lower_bound,upper_bound上界
*/


/*常见套路
1.求不同满足条件的区间个数：可以考虑分治  //2019牛客多校第三场G
2.找一个区间，使得值最大：考虑做dp[i][j],以i作为右端点「长度」为j的最大值 //CF1197D
3，找一个最长的区间满足条件：可以考虑线段树维护：hdu6602
*/