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

using namespace std;
#define pi acos(-1.0)
const int maxn=100005;
int len=0,n,a[4*maxn],num[4*maxn],bit=0,s=1,rev[4*maxn];
complex<double> b[4*maxn];

void fft(complex<double> *a,int t,int inv)
{
	for(int i=0;i<t;i++){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		if(i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for(int len=1;len<t;len*=2){
		complex<double> wn{cos(pi/len),inv*sin(pi/len)};
		for(int st=0;st<t;st+=2*len){
			complex<double> w{1.0,0.0};
			for(int j=st;j<st+len;j++,w*=wn){
				complex<double> x=a[j];
				complex<double> y=w*a[j+len];
				
				a[j]=x+y;
				a[j+len]=x-y;
			}
		}
	}
	if(inv==-1){
		for(int i=0;i<t;i++) a[i]/=t;
	}
}

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		num[a[i]]++;
		len=max(len,a[i]);
	}
	while(1<<(bit)<2*len) bit++,s<<=1;
	for(int i=0;i<s;i++) b[i]=(double)num[i];
	fft(b,s,1);   //DFT
	for(int i=0;i<s;i++) b[i]=b[i]*b[i]; 
	fft(b,s,-1);  //IDFT
	for(int i=0;i<s;i++) if((int)(b[i].real()+0.5)) printf("%d %d\n",i,(int)(b[i].real()+0.5));
}
