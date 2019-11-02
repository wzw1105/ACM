#include<bits/stdc++.h>
using namespace std;
#define eps 1e-8
int exunique(double *a,int n) {
	int tot=0;
	for(int point_=1;point_<=n;) {
		int cur=point_;
		while(point_<=n && a[point_]-a[cur]<=eps) point_++;
		a[++tot]=a[cur]; 
	}
	return tot;
}
double a[10005];
int main() {
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
	sort(a+1,a+n+1);
	int k=exunique(a,n);
	for(int i=1;i<=k;i++) printf("%.2lf%c",a[i],i==n?'\n':' '); 
}