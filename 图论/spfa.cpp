#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
const int maxm=5e5+10;
#define inf 0x3f3f3f3f

int head[maxn],inq[maxn],dis[maxn],n,m,tot=-1;
struct node{
	int to,w,next;
	node(int a=0,int b=0,int c=0){
		to=a,w=b,next=c;
	}
}edge[maxm];

void add_edge(int u,int v,int w) {
	edge[++tot]=node(v,w,head[u]);
	head[u]=tot;
}

void spfa(int s,int t) {
	memset(inq,0,sizeof(inq));
	memset(dis,0x3f,sizeof(dis));
	queue<int> que;que.push(s);
	inq[s]=1;dis[s]=0;
	while(!que.empty()){
		int cur=que.front();que.pop();inq[cur]=0;
		for(int i=head[cur];i!=-1;i=edge[i].next){
			int nxt=edge[i].to;
			if(dis[cur]+edge[i].w<dis[nxt]){
				dis[nxt]=dis[cur]+edge[i].w;
				if(!inq[nxt]){
					que.push(nxt);
					inq[nxt]=1;
				}
			}
		}
	}
}

int main()
{
	int s;scanf("%d %d %d",&n,&m,&s);
	memset(head,-1,sizeof(head));
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	spfa(s,0);
	for(int i=1;i<=n;i++) printf("%d%c",dis[i]==inf?2147483647:dis[i],i==n?'\n':' ');
}