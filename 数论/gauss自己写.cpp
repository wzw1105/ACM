#include<bits/stdc++.h>

using namespace std;
const int maxn=55;

int m,n,a[maxn][maxn],x[maxn];
bool fre[maxn]; //自由元

int gcd(int a,int b) {return b==0?a:gcd(b,a%b);}
int lcm(int a,int b) {return a/gcd(a,b)*b;}
int gauss() {
	int col=1,row=1;
	for(;row<=n&&col<=m;col++,row++){
		int cur=row;
		for(int i=row;i<=n;i++) if(abs(a[i][col])>abs(a[cur][row])) cur=i;
		if(cur!=row) for(int i=col;i<=m+1;i++) swap(a[row][i],a[cur][i]);
		if(a[row][col]==0) {row--;continue;}
		for(int i=row+1;i<=n;i++){
			if(a[i][col]!=0){
				int LCM=lcm(a[row][col],a[i][col]);
				int tmpa=LCM/a[row][col],tmpb=LCM/a[i][col];
				for(int j=col;j<=m+1;j++) a[i][j]=a[i][j]*tmpb-a[row][j]*tmpa;
			}
		}
	}
	if(row<=m) return m-row+1;
	for(int i=row;i<=n;i++) if(a[i][col]!=0) return -1;
	for(int i=n;i>=1;i--){
		int tmp=a[i][m+1];
		for(int j=i+1;j<=m;j++) tmp-=x[j]*a[i][j];
		if(tmp%a[i][i]!=0) return -2; //有浮点数解
		x[i]=tmp/a[i][i];
	}
	return 0;
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=m+1;j++) scanf("%d",&a[i][j]);
	int ans=gauss();
	if(ans==-1) printf("no answer\n");
	else if(ans==-2) printf("have float answer\n");
	else if(ans>0) printf("have inf answer\n");
	else for(int i=1;i<=n;i++) printf("x%d:%d%c",i,x[i],i==n?'\n':' ');
}
