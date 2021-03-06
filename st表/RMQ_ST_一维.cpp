#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,q,a[maxn],l,r;

namespace sparse_table{
	//dp[0]这一位用来弄最小值，dp[1]用来计算最大值，id用来记录对应位置
	int dp[2][maxn][20],id[2][maxn][20];
	void init() {
		for(int i=1;i<=n;i++) {
			dp[0][i][0]=dp[1][i][0]=a[i];
			id[0][i][0]=id[1][i][0]=i;
		}
		for(int j=1;(1<<j)<=n;j++){
			for(int i=1;(i+(1<<j)-1)<=n;i++){
				dp[0][i][j]=min(dp[0][i][j-1],dp[0][i+(1<<(j-1))][j-1]);
				dp[1][i][j]=max(dp[1][i][j-1],dp[1][i+(1<<(j-1))][j-1]);

				if(dp[0][i][j-1]<=dp[0][i+(1<<(j-1))][j-1]) 
					id[0][i][j]=id[0][i][j-1];  
				else id[0][i][j]=id[0][i+(1<<(j-1))][j-1];

				if(dp[1][i][j-1]>=dp[1][i+(1<<(j-1))][j-1]) 
					id[1][i][j]=id[1][i][j-1];
				else id[1][i][j]=id[1][i+(1<<(j-1))][j-1];
			}
		}
	}
	// 返回最小值与最大值，pair的first是最小值，second是最大值
	pair<int,int> query(int le,int ri) {
		if(le>ri) return make_pair(0,0);int k=0;
		while(le+(1<<(k+1))-1<=ri) k++;
		int mi=min(dp[0][le][k],dp[0][ri-(1<<k)+1][k]);
		int ma=max(dp[1][le][k],dp[1][ri-(1<<k)+1][k]);
		return make_pair(mi,ma);
	}
	//返回最小值与最大值的位置下标，前一个为最小值下标
	pair<int,int> query_id(int le,int ri) {
		if(le>ri) return make_pair(-1,-1);int k=0,mi,ma;
		while(le+(1<<(k+1))-1<=ri) k++;
		if(dp[0][le][k]<=dp[0][ri-(1<<k)+1][k]) mi=id[0][le][k];
		else mi=id[0][ri-(1<<k)+1][k];
		if(dp[1][le][k]>=dp[1][ri-(1<<k)+1][k]) ma=id[1][le][k];
		else ma=id[1][ri-(1<<k)+1][k];
		return make_pair(mi,ma);
	}
}
using namespace sparse_table;

int main() {
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	init();
	for(int i=1;i<=n;i++){
		scanf("%d %d",&l,&r);
		pair<int,int> ans_num=query(l,r),ans_id=query_id(l,r);
		printf("min:%d index:%d\n",l,r,ans_num.first,ans_id.first);
		printf("max:%d index:%d\n",l,r,ans_num.second,ans_id.second);
	}
}
