#include<bits/stdc++.h>

using namespace std;
const int maxn=5e3+10;
const int maxm=1e5+10;
#define inf 0x3f3f3f3f

int n,m,head[maxn],tot,max_flow,pre[maxn],inq[maxn],dis[maxn];
struct node{
	int to,w,c,next;
	node(int a=0,int b=0,int d=0,int e=0){
		to=a;w=b;c=d;next=e;
	}
}edge[maxm];

void add_edge(int u,int v,int w,int c) {
	edge[++tot]=node(v,w,c,head[u]);
	head[u]=tot;
}

bool spfa(int s,int t) {
	for(int i=1;i<=n;i++) dis[i]=0x3f3f3f3f,inq[i]=0,pre[i]=-1;
	queue<int> que;
	que.push(s),inq[s]=1,dis[s]=0;
	while(!que.empty()){
		int cur=que.front();que.pop();inq[cur]=0;
		for(int i=head[cur];i!=-1;i=edge[i].next){
			if(edge[i].w&&dis[cur]+edge[i].c<dis[edge[i].to]){
				dis[edge[i].to]=dis[cur]+edge[i].c;
				pre[edge[i].to]=i;
				if(!inq[edge[i].to]){
					que.push(edge[i].to);
					inq[edge[i].to]=1;
				}
			}
		}
	}
	return pre[t]!=-1;
}

int min_cost(int s,int t) {
	int cost=0;
	while(spfa(s,t)){
		int minn=inf;
		for(int i=t;i!=s;i=edge[pre[i]^1].to) minn=min(minn,edge[pre[i]].w);
		for(int i=t;i!=s;i=edge[pre[i]^1].to) {
			edge[pre[i]].w-=minn;
			edge[pre[i]^1].w+=minn;
			cost+=minn*edge[pre[i]].c;
		}
		max_flow+=minn;
	}
	return cost;
}

int main() {
	int s,t;scanf("%d %d %d %d",&n,&m,&s,&t);
	for(int i=1;i<=n;i++) head[i]=-1;tot=-1;  //初始化tot为-1而不是0
	for(int i=1,u,v,w,c;i<=m;i++){
		scanf("%d %d %d %d",&u,&v,&w,&c);
		add_edge(u,v,w,c);
		add_edge(v,u,0,-c);
	}
	int ans=min_cost(s,t);
	printf("%d %d\n",max_flow,ans);
}