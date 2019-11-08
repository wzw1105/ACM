#include<bits/stdc++.h>
using namespace std;
const int maxn=300005;
const int maxm=1000005;
#define inf 0x3f3f3f3f3f3f3f3f

struct edge{int u,v,w,next;}e[maxm];
int n,m,head[maxn],tot;
long long dis[maxn];
void add_edge(int u,int v,int w) {e[++tot]=edge{u,v,w,head[u]};head[u]=tot;}
void clear(int n)  {for(int i=1;i<=n;i++) head[i]=0;tot=0;}

long long dijkstra(int s) {
    priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > que;
    for(int i=1;i<=n;i++) dis[i]=inf;
    dis[s]=0,que.push(make_pair(0,s));
    while(!que.empty()){
        pair<long long,int> cur=que.top();que.pop();
        if(dis[cur.second]<cur.first) continue;
        for(int i=head[cur.second];i;i=e[i].next) {
            if(dis[e[i].v] > cur.first + e[i].w) {
                dis[e[i].v] = cur.first + e[i].w;
                que.push(make_pair(dis[e[i].v], e[i].v));
            }
        }
    }
    return dis[n]==inf?-1:dis[n];
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	printf("%lld\n",dijkstra(1));
}
