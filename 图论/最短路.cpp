#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
#define pii pair<int,int>

struct node{int v,w;}edge;
int n,m,u,v,w,dis[maxn];
vector<node> vec[maxn];
void add_edge(int a,int b,int c) {vec[a].push_back(node{b,c});}
void dijkstra(int s) {
	priority_queue<pii,vector<pii>,greater<pii> > que;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	que.push(pii(0,s));
	while(!que.empty()){
		pii cur=que.top();que.pop();
		if(dis[cur.second]<cur.first) continue;
		for(int i=0;i<vec[cur.second].size();i++){
			node nxt=vec[cur.second][i];
			if(dis[nxt.v]>dis[cur.second]+nxt.w){
				dis[nxt.v]=dis[cur.second]+nxt.w;
				que.push(pii(dis[nxt.v],nxt.v));
			}
		}
	}
	printf("%d\n",dis[n]);
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	dijkstra(1);
}
