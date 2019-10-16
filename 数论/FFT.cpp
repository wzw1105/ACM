#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<set>
#include<ctime>
#include<cstdlib>
#include<limits>
#include<complex>

using namespace std;

#define pii pair<int, int>
#define cp complex<double>
#define mem(a,b) memset(a,b,sizeof(a))
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,a,b) for(int i=(a);i>=(b);i--)
#define pi acos(-1.0)
#define inf 0x3f3f3f3f
#define Rand() (rand()|rand()<<15)
#define Srand() srand(time(0)^(unsigned)(unsigned long long)(new char))
#define typemax(type)   numeric_limits<type>::max()
#define typemin(type)   numeric_limits<type>::min()
#define debug
typedef long long ll;

template<typename T> inline void read(T &x) {x = 0;int f = 1;char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}x=x*f;}
template<typename E> E gcd(E a,E b){return b==0?a:gcd(b,a%b);}
template<typename E> E lcm(E a,E b){return a*b/gcd(a,b);}
template<typename E> E ex_gcd(E a,E b,E &x,E&y) {if(b==0){x=1;y=0;}else {ex_gcd(b,a%b,y,x);y-=(a/b)*x;}}
template<typename E> E quick_mul(E a,E b,E c){E ans=0;while(b){if(b&1) ans=(ans+a)%c;a=(a+a)%c;b>>=1;}  return ans;}
template<typename E> E quick_pow(E a,E b,E c){E ans=1;while(b){if(b&1) ans=ans*a%c;a=a*a%c;b>>=1;}return ans;}
template<typename E> E inv1(E a,E b){return quick_pow(a,b-2,b);}
template<typename E> E inv2(E a,E b){E x,y;ex_gcd(a,b,x,y);return (x%b+b)%b;}

/*==================================Header Template=============================================*/

using namespace std;
const int maxn=100005;
int len=0,n,a[4*maxn],num[4*maxn],bit=0,s=1,rev[4*maxn];
cp b[4*maxn];

void fft(cp *a,int t,int inv)
{
	per(i,0,t-1){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		if(i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for(int len=1;len<t;len*=2){
		cp wn{cos(pi/len),inv*sin(pi/len)};
		for(int st=0;st<t;st+=2*len){
			cp w{1.0,0.0};
			for(int j=st;j<st+len;j++,w*=wn){
				cp x=a[j];
				cp y=w*a[j+len];
				
				a[j]=x+y;
				a[j+len]=x-y;
			}
		}
	}
	if(inv==-1){
		for(int i=0;i<t;i++) a[i]/=t;
	}
}

int main()
{
#ifdef debug
	freopen("C:\\Users\\ÍõÖ¾Î°\\Desktop\\in.txt","r",stdin);
	int tt=clock();
#endif

	scanf("%d",&n);
	per(i,1,n){
		scanf("%d",&a[i]);
		num[a[i]]++;
		len=max(len,a[i]);
	}
	while(1<<(bit)<2*len) bit++,s<<=1;
	per(i,0,s-1) b[i]=(double)num[i];
	fft(b,s,1);   //DFT
	for(int i=0;i<s;i++) b[i]=b[i]*b[i]; 
	fft(b,s,-1);  //IDFT
	per(i,0,s-1) if((int)(b[i].real()+0.5)) printf("%d %d\n",i,(int)(b[i].real()+0.5));
	
#ifdef debug
	printf("%d\n",clock()-tt);
#endif
}
