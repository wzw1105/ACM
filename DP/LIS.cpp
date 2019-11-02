#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
int dp[100005];
int LIS(int a[],int n) {//longest increasing sequence
	for(int i=0;i<=n;i++) dp[i]=inf;
	for(int i=1;i<=n;i++) *lower_bound(dp+1,dp+n+1,a[i])=a[i];
	return lower_bound(dp+1,dp+n+1,inf)-dp-1;
}
int LNDS(int a[],int n) {//longest not decreasing sequence
	for(int i=0;i<=n;i++) dp[i]=inf;
	for(int i=1;i<=n;i++) *upper_bound(dp+1,dp+n+1,a[i])=a[i];
	return lower_bound(dp+1,dp+n+1,inf)-dp-1;
}
int n,a[100005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	printf("%d %d\n",LIS(a,n),LNDS(a,n)); 
}