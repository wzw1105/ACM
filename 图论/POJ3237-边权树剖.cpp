#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;
typedef long long ll;
const int maxn=1e5+10;

//存树
struct edge{
	int to,id;
	edge(int a=0,int b=0){
		to=a;id=b;
	}
}son[maxn];
vector<edge> vec[maxn];

//树剖用
int h[maxn],fa[maxn],top[maxn],id[maxn],siz[maxn],rk[maxn],ed[maxn],tot;

//题目数据
int t,n,num,u[maxn],v[maxn],a,b;ll val[maxn],c;
char opt[20];

struct node{
	int l,r,opt;
	ll minn,maxx;
}tree[maxn<<2];

struct segment_tree{
	void build(int le,int ri,int id){
		tree[id].l=le,tree[id].r=ri;tree[id].opt=0;
		if(le==ri) {
			tree[id].minn=tree[id].maxx=val[rk[le]];
			return;
		}
		int mid=(le+ri)>>1;
		build(le,mid,id<<1);
		build(mid+1,ri,id<<1|1);
		pushup(id);
	}

	void pushup(int id){
		tree[id].maxx=max(tree[id<<1].maxx,tree[id<<1|1].maxx);
		tree[id].minn=min(tree[id<<1].minn,tree[id<<1|1].minn);
	}

	void down(int id){
		tree[id<<1].opt=(tree[id<<1].opt+tree[id].opt)%2;
		tree[id<<1|1].opt=(tree[id<<1|1].opt+tree[id].opt)%2;
		ll x=tree[id<<1].minn,y=tree[id<<1].maxx;
		tree[id<<1].minn=-y;tree[id<<1].maxx=-x;
		x=tree[id<<1|1].minn,y=tree[id<<1|1].maxx;
		tree[id<<1|1].minn=-y;tree[id<<1|1].maxx=-x;
		tree[id].opt=0;
	}

	int len(int id){
		return tree[id].r-tree[id].l+1;
	}

	void update(int l,int r,int id){
		if(l<=tree[id].l&&r>=tree[id].r){
			tree[id].opt=(tree[id].opt+1)%2;
			ll a=tree[id].minn,b=tree[id].maxx;
			tree[id].minn=-b;tree[id].maxx=-a;
			return;
		}
		if(tree[id].opt) down(id);
		int mid=(tree[id].l+tree[id].r)>>1;
		if(l<=mid) update(l,r,id<<1);
		if(r>mid) update(l,r,id<<1|1);
		pushup(id);
	}

	ll query(int l,int r,int id){
		ll ans=-1e18;
		if(l<=tree[id].l&&r>=tree[id].r) return tree[id].maxx;

		if(tree[id].opt) down(id);
		int mid=(tree[id].l+tree[id].r)>>1;
		if(l<=mid) ans=max(ans,query(l,r,id<<1));
		if(r>mid) ans=max(ans,query(l,r,id<<1|1));

		pushup(id);
		return ans;
	}

	void modify(int k,int id,ll val){
		if(tree[id].l==tree[id].r) {
			tree[id].minn=tree[id].maxx=val;
			tree[id].opt=0;
			return;
		}

		if(tree[id].opt) down(id);
		int mid=(tree[id].l+tree[id].r)>>1;
		if(k<=mid) modify(k,id<<1,val);
		else modify(k,id<<1|1,val);

		pushup(id);
	}
}data;

struct tree_{
	void init(){
		tot=-1;
		for(int i=1;i<=n;i++) son[i].id=son[i].to=0;
		memset(h,0,sizeof(h));
	}

	void build(){
		dfs1(1,0,1,0);dfs2(1,1,0);
		data.build(1,n-1,1);
	}

	void dfs1(int cur,int fath,int he,int id){ //dfs(root,0,1)
 		h[cur]=he;fa[cur]=fath;siz[cur]=1;
 		if(u[id]!=fath) swap(u[id],v[id]);
 		for(int i=0;i<(int)vec[cur].size();i++){
 			edge nxt=vec[cur][i];
 			if(nxt.to!=fath){
 				dfs1(nxt.to,cur,he+1,nxt.id);
 				siz[cur]+=siz[nxt.to];
 				if(siz[nxt.to]>siz[son[cur].to]) son[cur]=nxt;
 			}
		}
	}


	void dfs2(int cur,int topp,int idd){ //dfs2(root,root)
		id[cur]=++tot;rk[tot]=idd;ed[idd]=tot;top[cur]=topp;
		if(son[cur].to) dfs2(son[cur].to,topp,son[cur].id);
		for(int i=0;i<(int)vec[cur].size();i++){
			edge nxt=vec[cur][i];
			if(nxt.to!=fa[cur]&&nxt.to!=son[cur].to){
				dfs2(nxt.to,nxt.to,nxt.id);
			}
		}
	}

	ll query(int x,int y){
		int topx=top[x],topy=top[y];ll ans=-1e18;
		while(topx!=topy){
			if(h[topx]>=h[topy]){
				ans=max(ans,data.query(id[topx],id[x],1));
				x=fa[topx],topx=top[x];
			}else{
				ans=max(ans,data.query(id[topy],id[y],1));
				y=fa[topy],topy=top[y];
			}
		}
		if(abs(id[x]-id[y])>=1) ans=max(ans,data.query(min(id[x],id[y])+1,max(id[x],id[y]),1));
		return ans;
	}

	void update(int x,int y){
		int topx=top[x],topy=top[y];
		while(topx!=topy){
			if(h[topx]>=h[topy]){
				data.update(id[topx],id[x],1);
				x=fa[topx],topx=top[x];
			}else{
				data.update(id[topy],id[y],1);
				y=fa[topy],topy=top[y];
			}
		}
		if(abs(id[x]-id[y])>=1) data.update(min(id[x],id[y])+1,max(id[x],id[y]),1);
	}

	void modify(int x,ll val){
		data.modify(ed[x],1,val);
	}
}chain;

int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);chain.init();
		for(int i=1;i<=n;i++) vec[i].clear();
		for(int i=1;i<n;i++){
			scanf("%d %d %lld",&u[i],&v[i],&val[i]);
			vec[u[i]].push_back(edge(v[i],i));
			vec[v[i]].push_back(edge(u[i],i));
		}
		chain.build();
		while(true){
			scanf("%s",opt+1);
			if(opt[1]=='D') break;

			if(opt[1]=='C') {
				scanf("%d %lld",&a,&c);
				chain.modify(a,c);
			}else if(opt[1]=='N'){
				scanf("%d %d",&a,&b);
				chain.update(a,b);
			}else {
				scanf("%d %d",&a,&b);
				printf("%lld\n",chain.query(a,b));
			}
		}
	}
}