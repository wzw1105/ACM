//给一个图，判断是否是是一棵树
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
const int maxn=200005;
set<int> s;

int fa[maxn],dep[maxn],tot=0,ru[maxn],u,v,n;
struct node{
	int u,v;
	node(int a=0,int b=0){
		u=a;v=b;
	}
}edge[maxn];

void init(){	
	memset(dep,0,sizeof(dep));
	memset(ru,0,sizeof(ru));
	s.clear();tot=0;n=0;
}

int fin(int u) {return fa[u]==u?u:fin(fa[u]);}
void merge(int u,int v) {
	int x=fin(u),y=fin(v);
	if(dep[x]<=dep[y]){
		fa[x]=fa[y];
		if(dep[x]==dep[y]) dep[y]++;
	}else fa[y]=fa[x];
}
int main() {
	for(int cas=1;;cas++){
		init();
		while(true){
			scanf("%d %d",&u,&v);
			if(u==0&&v==0) break;
			else if(u==-1&&v==-1) return 0;
			else{
				ru[v]++;
				edge[++tot]=node(u,v);
				n=max(u,max(n,v));
				s.insert(u);
				s.insert(v);
			}
		}
		//判断是否有入度>1
		bool flag=true;
		for(int i=1;i<=n;i++) if(ru[i]>=2) {flag=false;break;}
		if(!flag) {printf("Case %d is not a tree.\n",cas);continue;}
		//判断是否成环
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=tot;i++){
			int x=fin(edge[i].u),y=fin(edge[i].v);
			if(x==y) {flag=false;break;}
			else merge(edge[i].u,edge[i].v);
		}
		//判断是否有森林
		int tot=0;
		for(set<int>::iterator it=s.begin();it!=s.end();it++) {
			int i=*it;
			if(fa[i]==i) tot++;
		}
		if(tot>1) flag=false;
		if(flag) printf("Case %d is a tree.\n",cas);
		else printf("Case %d is not a tree.\n",cas);
	}
}