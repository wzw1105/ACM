template<typename T> inline void read(T &x) {
	x = 0;int f = 1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	x=x*f;
}

//最大公约数和最小公倍数
int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int lcm(int a,int b) {return a*b/gcd(a,b);}

//拓展欧几里得
int ex_gcd(int a,int b,int &x,int &y) {
	if(b==0) x=1,y=0;
	else ex_gcd(b,a%b,y,x),y-=(a/b)*x;
}

//慢速乘求(a*b)%c,目的是方式两数相乘爆long long或者int
int quick_mul(int a,int b,int c){
	int ans=0;
	while(b){
		if(b&1) ans=(ans+a)%c;
		a=(a+a)%c;
		b>>=1;
	}  
	return ans;
}

//快速幂求(a^b)%c
long long quick_pow(long long a,long long b,long long c) {
	long long ans=1;
	while(b){
		if(b&1) ans=ans*a%c;
		a=a*a%c;
		b>>=1;
	}
	return ans;
}

//求a关于模数b的逆元
long long inv1(long long a,long long b) {return quick_pow(a,b-2,b);}
//long long inv2(long long a,long long b) {long long x,y;ex_gcd(a,b,x,y);return (x%b+b)%b;}
