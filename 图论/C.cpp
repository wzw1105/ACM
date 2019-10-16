#include<bits/stdc++.h>

using namespace std;
const int maxn=5e5+10;

struct dsu{
	int fa[maxn],rank[maxn];
	void init(int k){
		for(int i=1;i<=k;i++) fa[i]=i,rank[i]=0;
	}
	int fin(int k){
		return fa[k]==k?k:(fa[k]=fin(fa[k]));
	}
	
	void unite(int a,int b){
		int x=fin(a),y=fin(b);
		if(x==y) return;
		if(rank[x]<rank[y]) 
		fa[x]=y;
		else{
			fa[y]=x;
			if(rank[x]==rank[y]) rank[x]++;
		}
	}
	
	bool same(int a,int b){
		return fin(a)==fin(b);
	}
}tree;

int n,m,u,k,b[maxn],ans[maxn];

int main()
{
	scanf("%d %d",&n,&m);

	tree.init(n);
	for(int i=1;i<=m;i++){
		scanf("%d",&k);
		for(int j=1;j<=k;j++){
			scanf("%d",&b[j]);
		}
		for(int j=2;j<=k;j++){
			tree.unite(b[j],b[j-1]);
		}
	}

	for(int i=1;i<=n;i++) ans[tree.fin(i)]++;
	for(int i=1;i<=n;i++) printf("%d ",ans[tree.fin(i)]);
}