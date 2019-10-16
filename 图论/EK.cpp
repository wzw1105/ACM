#include<bits/stdc++.h>

using namespace std;
#define inf 0x3f3f3f3f
const int maxn=2e5+10;

int head[maxn],tot;bool vis[maxn];
struct ed{
	int to,next,w;
	ed(int a=0,int b=0,int c=0){
		to=a;next=b;w=c;
	}
}edge[maxn];
struct path{
	int to,id;
	path(int a=0,int b=0){
		to=a;id=b;
	}
}pre[maxn];

void init(int n) {
	for(int i=1;i<=n;i++) head[i]=-1;
	tot=-1;
}

void add_edge(int u,int v,int w) {
	edge[++tot]=ed(v,head[u],w);
	head[u]=tot;
}

bool bfs(int s,int t) {
	queue<int> que;que.push(s);
	memset(vis,false,sizeof(vis));vis[s]=true;
	while(!que.empty()){
		int cur=que.front();que.pop();
		for(int i=head[cur];i!=-1;i=edge[i].next){
			int next_=edge[i].to;
			if(!vis[next_]&&edge[i].w){
				pre[next_]=path(cur,i);
				que.push(next_);vis[next_]=true;
				if(next_==t) return true;
			}
		}
	}
	return false;
}

int ek(int s,int t){
	int max_flow=0; 
	while(bfs(s,t)){
		int minn=inf;
		for(int cur=t;cur!=s;cur=pre[cur].to) minn=min(minn,edge[pre[cur].id].w);
		for(int cur=t;cur!=s;cur=pre[cur].to) {
			edge[pre[cur].id].w-=minn;
			edge[pre[cur].id^1].w+=minn;
		}
		max_flow+=minn;
	}
	return max_flow;
}

int main()
{
	int t;scanf("%d",&t);
	for(int cas=1,m,n,u,v,w;cas<=t;cas++){
		scanf("%d %d",&n,&m);init(n);
		for(int i=1;i<=m;i++){
			scanf("%d %d %d",&u,&v,&w);
			add_edge(u,v,w);
			add_edge(v,u,0);
		}
		printf("Case %d: %d\n",cas,ek(1,n));
	}
}