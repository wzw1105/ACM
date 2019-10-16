#include<bits/stdc++.h>

using namespace std;

const int mod=10000;
int dp[105][10005],m,n;

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)dp[i][0]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<=i-1&&j-k>=0;k++){
				dp[i][j]=(dp[i][j]+dp[i-1][j-k])%mod;
			}
		}
	}
	printf("%d\n",dp[n][m]);
}
