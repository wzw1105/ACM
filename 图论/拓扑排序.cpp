#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+10;

vector<int> vec[maxn];
int topo[maxn],vis[maxn],n,m,u,v,len; 

bool dfs(int cur) {
	vis[cur]=-1;
	for(int i=0;i<vec[cur].size();i++){
		if(vis[vec[cur][i]]<0) return false;
		else if(!vis[vec[cur][i]] && !dfs(vec[cur][i])) return false;
	}
	vis[cur]=1,topo[len--]=cur;
	return true;
}

bool toposort() {
	len=n;
	for(int i=1;i<=n;i++) vis[i]=false;
	for(int i=1;i<=n;i++) if(!vis[i]) if(!dfs(i)) return false;
	return true;
}

int main() {
	int t;scanf("%d",&t);
	while(~scanf("%d %d",&n,&m)){
		for(int i=1;i<=n;i++) vec[i].clear();
		for(int i=1;i<=m;i++){
			scanf("%d %d",&u,&v);
			vec[u].push_back(v);
		}
		if(toposort()) for(int i=1;i<=n;i++) printf("%d%c",topo[i],i==n?'\n':' ');
	}
}
