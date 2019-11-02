#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
const int maxm=2e5+10; //注意每条边都有反向边
#define inf 0x3f3f3f3f

int dis[maxn],head[maxn],id[maxn],tot,n,m;//id:当前弧优化,即记录可用的最远的那条边
struct node{
	int to,w,next;
	node(int a=0,int b=0,int c=0){
		to=a;w=b;next=c;
	}
}edge[maxm];

void add_edge(int u,int v,int w) {
	edge[++tot]=node(v,w,head[u]);
	head[u]=tot;
}

bool bfs(int s,int t) {
	queue<int> que;que.push(s);
	for(int i=1;i<=n;i++) dis[i]=0,id[i]=head[i];dis[s]=1;  //注意这里的n的范围，不注意经常死循环
	while(!que.empty()){
		int cur=que.front();que.pop();
		for(int i=head[cur];i!=-1;i=edge[i].next){
			int nxt=edge[i].to;
			if(edge[i].w&&!dis[nxt]){
				dis[nxt]=dis[cur]+1;
				que.push(nxt);
				if(nxt==t) return 1;
			}
		}
	}
	return 0;
}

int dfs(int cur,int flow,int s,int t) {
	if(cur==t) return flow;
	int rest=flow;
	for(int i=id[cur];i!=-1&&rest;i=edge[i].next){
		id[cur]=i;
		if(edge[i].w&&dis[edge[i].to]==dis[cur]+1){
			int f=dfs(edge[i].to,min(rest,edge[i].w),s,t);
			edge[i].w-=f;
			edge[i^1].w+=f;
			rest-=f;
		}
	}
	return flow-rest;
}

inline int dinic(int s,int t){
	int maxflow=0,flow;
	while(bfs(s,t)) while((flow=dfs(s,inf,s,t))) maxflow+=flow;
	return maxflow;
}

int main(){
	int t;scanf("%d",&t);
	for(int cas=1;cas<=t;cas++){
		scanf("%d %d",&n,&m);
		memset(head,-1,sizeof(head));tot=-1;
		for(int i=1,u,v,w;i<=m;i++){
			scanf("%d %d %d",&u,&v,&w);
			add_edge(u,v,w);
			add_edge(v,u,0);
		}
		printf("Case %d: %d\n",cas,dinic(1,n));
	}
}