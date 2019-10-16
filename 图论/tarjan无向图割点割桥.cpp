#include<bits/stdc++.h>

using namespace std;
const int maxn=300005;
const int maxm=300005;

int n,m,u,v,dfn[maxn],low[maxn],sta[maxn],belong[maxn],tot=0,tim=0,block=0;
int head[maxn],num=0;
bool insta[maxn];
bool cut_node[maxn],cut_edge[maxm]; //cut_node表示割点，cut_edge表示割桥

struct node{
	int u,v,pre;
	node(int a=0,int b=0,int c=0){
		u=a;v=b;pre=c;
	}
}edge[maxm];

void add_edge(int u,int v) {
	edge[++num]=node(u,v,head[u]);
	head[u]=num;
}

void init() {
	tot=tim=block=num=0;
	memset(cut_node,false,sizeof(cut_node));
	memset(cut_edge,false,sizeof(cut_edge));
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
}

//tarjan求无向图割点割边
void tarjan(int cur,int fa)
{
	insta[cur]=true;
	sta[++tot]=cur;
	dfn[cur]=low[cur]=++tim;
	int child=0,pre_cnt=0;
	for(int i=head[cur];i;i=edge[i].pre){
		if(edge[i].v==fa&&!pre_cnt){
			pre_cnt=1;
			continue;
		}
		if(!dfn[edge[i].v]){
			child++;
			tarjan(edge[i].v,cur);
			low[cur]=min(low[cur],low[edge[i].v]);
			if(low[edge[i].v]>=dfn[cur]){
				cut_node[cur]=true;
				if(low[edge[i].v]>dfn[cur]){
					cut_edge[i]=true;
				}
			}
		}else if(insta[edge[i].v]){   //dfn[edge[i].v]<dfn[cur]&&edge[i].v!=fa
			low[cur]=min(low[cur],dfn[edge[i].v]);
		}
	}
	if(!fa&&child==1) cut_node[cur]=false;
	if(dfn[cur]==low[cur]){
		++block;int topv;
		do{
			topv=sta[tot--];
			belong[topv]=block;
			insta[topv]=false;
		}while(topv!=cur);
	}
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
	int ans=0;
	for(int i=1;i<=2*m;i++) if(cut_edge[i]) ans++;
	printf("%d\n",m-ans);
}
