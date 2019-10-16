#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;


//st
int n,a[maxn],dp[maxn][20],p[maxn][20],Log[maxn];
void init_st(int a[],int n)
{
    Log[0]=-1;for(int i=1;i<=n;i++) Log[i]=Log[i>>1]+1; 
    for(int i=1;i<=n;i++) dp[i][0]=a[i],p[i][0]=i;
    for(int j=1;(1<<j)<=n;j++) for(int i=1;i+(1<<j)-1<=n;i++) {
        dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        //if(dp[i][j-1]>=dp[i+(1<<(j-1))][j-1]) p[i][j]=p[i][j-1];
        //else p[i][j]=p[i+(1<<(j-1))][j-1];
    }
}

int query(int l,int r)
{
    int k=Log[r-l+1];
    return max(dp[l][k],dp[r-(1<<k)+1][k]);
    //if(dp[l][k]>=dp[r-(1<<k)+1][k]) return p[l][k];
    //return p[r-(1<<k)+1][k];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init_st(a,n);
	int q,l,r;
	scanf("%d",&q);
	while(q--) {
		scanf("%d %d",&l,&r);
		printf("%d\n",query(l,r));
	}
}