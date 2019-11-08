/*
bzoj3040:求1到n的最短路 n<=1e6 m<=1e7
普通dijkstra的复杂度(n+m)log(n+m)
使用配对堆优化后的复杂度为(n+m)log n
优化原理就是堆中同一个节点最多出现1次，因为这样做是改节点的值而不是直接插
*/
#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<pair<long long,int>,greater<pair<long long,int> >,pairing_heap_tag > heap;

const int maxn=1e6+5;
const int maxm=1e7+5;
#define inf 0x3f3f3f3f

heap::point_iterator id[maxn];
struct edge{int u,v,w,next;}e[maxm];
int n,m,head[maxn],tot;
long long dis[maxn];
void add_edge(int u,int v,int w) {e[++tot]=edge{u,v,w,head[u]};head[u]=tot;}
void clear(int n)  {for(int i=1;i<=n;i++) head[i]=0;tot=0;}

long long dijkstra(int s,int n) {
	heap que;
	for(int i=1;i<=n;i++) dis[i]=inf;
	dis[1]=0,id[1]=que.push(make_pair(0,1));
	while(!que.empty()) {
		pair<long long,int> cur=que.top();que.pop();
		for(int i=head[cur.second];i;i=e[i].next) {
			if(dis[e[i].v] > cur.first + e[i].w) {
				dis[e[i].v] =cur.first + e[i].w;
				if(id[e[i].v]!=0) que.modify(id[e[i].v],make_pair(dis[e[i].v],e[i].v));
				else id[e[i].v]=que.push(make_pair(dis[e[i].v],e[i].v));
			}
		} 
	}
	return dis[n];
}

int T,rxa,rxc,rya,ryc,rp;
int main() {
	scanf("%d %d %d %d %d %d %d %d",&n,&m,&T,&rxa,&rxc,&rya,&ryc,&rp);
	for(int i=1,x=0,y=0,z=0,a,b;i<=T;i++) {
		x=(1LL*x*rxa+rxc)%rp;
		y=(1LL*y*rya+ryc)%rp;
		a=min(x%n+1,y%n+1);
		b=max(y%n+1,y%n+1);
		add_edge(a,b,1e8-100*a);
	}
	for(int i=1,u,v,w;i<=m-T;i++) {
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	printf("%lld\n",dijkstra(1,n));
}
