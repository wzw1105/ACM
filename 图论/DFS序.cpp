#include<bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define mem(a,b) memset(a,b,sizeof(a))
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,a,b) for(int i=(a);i>=(b);i--)
#define pi acos(-1.0)
#define inf 0x3f3f3f3f
typedef long long ll;

template <class T> inline void read(T &x) {
	x = 0;int f = 1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x=x*f;
}
template<typename E> E gcd(E a,E b){return b==0?a:gcd(b,a%b);}
template<typename E> E ex_gcd(E a,E b,E &x,E&y) {if(b==0){x=1;y=0;}else {ex_gcd(b,a%b,y,x);y-=(a/b)*x;}}
template<typename E> E quick_pow(E a,E b,E c){E ans=1;while(b){if(b&1) ans=ans*a%c;a=a*a%c;b>>=1;}return ans;}
template<typename E> E inv1(E a,E b){return quick_pow(a,b-2,b);}
template<typename E> E inv2(E a,E b){E x,y;ex_gcd(a,b,x,y);return (x%b+b)%b;}

/*================Header Template==============*/

const double eps=1.0e-5;
const int maxn=200000+10;
const ll mod=10007;

int len=0,dfs_xv[200005],tim=0,a,b,n,m,s[200005],e[200005]; 
vector<int> vec[200005];

void dfs(int k)
{
	dfs_xv[++len]=k;
	s[k]=len; 
	for(int i=0;i<vec[k].size();i++){
		dfs(vec[k][i]);
	}	
	e[k]=len;
}

int main()
{
	scanf("%d",&n);
	per(i,1,n){
		scanf("%d",&m);
		per(j,1,m){
			scanf("%d",&a);
			vec[i].push_back(a);
		}
	}
	
	dfs(1);
	per(i,1,len) printf("%d ",dfs_xv[i]);puts("");
	per(i,1,n) printf("%d ",s[i]);puts("");
	per(i,1,n) printf("%d ",e[i]);puts("");
}

/*
13
2 10 3
1 7
2 4 5
0
2 2 6
0
0
0
1 11
2 12 9
2 8 13
0
0
*/
