#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>

using namespace std;
const int maxn=5005;
const int inf=0x3f3f3f3f;
int dis1[maxn],dis2[maxn],u,v,w,n,m;

struct node{
	int pos,w;
	node(int a=0,int b=0){
		pos=a;w=b;
	}
	friend bool operator<(const node&a,const node &b){
		return a.w>b.w;
	}
};

vector<node> vec[maxn];

void add_edge(int a,int b,int c) {
	vec[a].push_back(node(b,c));
	vec[b].push_back(node(a,c));
} 
 
void dijkstra2(int s,int to) {
	priority_queue<node> que;
	memset(dis1,0x3f,sizeof(dis1));
	memset(dis2,0x3f,sizeof(dis2));
	dis1[s]=0;
	que.push(node(s,0));
	while(!que.empty()){
		node cur=que.top();que.pop();
		if(dis2[cur.pos]<cur.w) continue;
		for(int i=0;i<vec[cur.pos].size();i++){
			int nxtw=cur.w+vec[cur.pos][i].w;
			if(nxtw<dis1[vec[cur.pos][i].pos]){
				swap(nxtw,dis1[vec[cur.pos][i].pos]);
				que.push(node(vec[cur.pos][i].pos,dis1[vec[cur.pos][i].pos]));
			}
			if(dis2[vec[cur.pos][i].pos]>nxtw&&nxtw>dis1[vec[cur.pos][i].pos]){
				dis2[vec[cur.pos][i].pos]=nxtw;
				que.push(node(vec[cur.pos][i].pos,nxtw));
			}
		}
	}
	printf("%d\n",dis2[to]);
	
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
	}
	dijkstra2(1,n);
}
