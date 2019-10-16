#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;

int n,m,u,v,dfn[maxn],low[maxn],head[maxn],sta[maxn],tot,len,tim;
bool vis[maxn]; 
struct ed{int to,w,nxt;}edge[maxn];

inline void init(int n) {
	tot=len=tim=0;
	for(int i=1;i<=n;i++) dfn[i]=low[i]=0;
}

inline void tarjan(int u) {
	vis[u]=true;
	sta[++tot]=u;
	dfn[u]=low[u]=++tim;
	for(int i=head[u];i;i=edge[i].nxt){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[u]=min(low[u],low[edge[i].to]);
		}else if(vis[edge[i].to]) low[u]=min(low[u],dfn[edge[i].to]);
	}
	if(dfn[u]==low[u]){
		while(sta[tot]!=u){
			vis[tot]=false;
			printf("%d ",sta[tot--]);
		}
		printf("%d\n",u);vis[u]=false;
		tot--;
	}
	
}

inline void add_edge(int u,int v,int w) {
	edge[++len]=ed{v,w,head[u]};
	head[u]=len;
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		add_edge(u,v,1);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	return 0;
} 
 
/*
5 5
1 2
2 3
3 4
4 5
5 3
*/ 
