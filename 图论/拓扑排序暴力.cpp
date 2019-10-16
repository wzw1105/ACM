#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;

int n,m,topo[maxn],len,u,v,ru[maxn];
queue<int> que;
vector<int> vec[maxn];
bool vis[maxn];

bool toposort() {
	for(int i=1;i<=n;i++) if(!ru[i]) que.push(i);
	while(len!=n){
		if(que.empty()) return false;
		int cur=topo[++len]=que.front();que.pop();
		for(int i=0;i<vec[cur].size();i++){
			ru[vec[cur][i]]--;
			if(ru[vec[cur][i]]==0) que.push(vec[cur][i]);
		}
	}
	return len==n;
	
}
inline void clear_(int n) {
	for(int i=1;i<=n;i++) vec[i].clear(),ru[i]=vis[i]=0;
}

int main() {
	while(~scanf("%d %d",&n,&m)){
		for(int i=1;i<=m;i++) {
			scanf("%d %d",&u,&v);
			vec[u].push_back(v);
			ru[v]++;
		}
		if(toposort()) for(int i=1;i<=n;i++) printf("%d%c",topo[i],i==n?'\n':' ');
		clear_(n);
	}
}
