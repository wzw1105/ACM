/*
洛谷P5043:给出m棵树,编号[1,m],求与第i棵树同构的最小编号的树
*/

#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
const int base=23333;
const long long mod=998244353;
int ans[maxn][maxn],fa[maxn],n,m,a[maxn];
vector<int> vec[maxn];

long long dfs(int cur,int fa) {
	vector<long long> sta;long long ans=base;
	for(int i=0;i<vec[cur].size();i++) if(vec[cur][i]!=fa) sta.push_back(dfs(vec[cur][i],cur));
	sort(sta.begin(),sta.end());
	for(int i=0;i<sta.size();i++) ans=(ans*base+sta[i])%mod;
	return ans;
}

int main() {
	scanf("%d",&m);
	for(int i=1;i<=m;i++) {
		scanf("%d",&a[i]); //n of each tree
		n=a[i];
		for(int j=1;j<=n;j++) {
			scanf("%d",&fa[j]);
			if(!fa[j]) continue;
			vec[j].push_back(fa[j]);
			vec[fa[j]].push_back(j);
		}
		for(int j=1;j<=n;j++) ans[i][j]=dfs(j,0);
		sort(ans[i],ans[i]+n+1);
		int same=i;
		for(int j=1;j<n;j++) {
			bool ok=true;
			if(a[i]!=a[j]) continue;
			for(int k=1;k<=n;k++) if(ans[j][k]!=ans[i][k]) {ok=false;break;}
			if(ok) {same=j;break;}
		}
		printf("%d\n",same);
		for(int i=1;i<=n;i++) vec[i].clear();
	}
}