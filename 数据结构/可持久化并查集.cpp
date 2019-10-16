#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;
const int maxn=2e5+10;

int n,m,type,a,b,old;

struct chairman_tree{
	int fa[maxn*50],cnt,tot; //fa数组记录主席树id为i的父亲的节点编号
	int point[maxn*50];   //映射主席树id为i的节点编号
	int dep[maxn*50];      //树深度
	int ls[maxn*50],rs[maxn*50];
	int roo[maxn];   //版本为i的根节点

	chairman_tree(){
		memset(fa,0,sizeof(fa));
		cnt=tot=0;
	}

	int build(int l,int r){
		int now=++cnt;
		if(l==r) {
			point[now]=l;
			return now;
		}
		int mid=(l+r)>>1;
		ls[now]=build(l,mid);
		rs[now]=build(mid+1,r);
		return now;
	}
	int modify(int l,int r,int posa,int posb,int ida,int idb,int pre){  //posa,posb节点编号，ida,idb主席树节点编号
		int now=++cnt;
		if(l==r){
			fa[now]=posb;
			if(dep[ida]==dep[idb]) dep[idb]++ ;
			point[now]=posb;
			return now;
		}
		int mid=(l+r)>>1;
		if(posa<=mid){
			rs[now]=rs[pre];
			ls[now]=modify(l,mid,posa,posb,ida,idb,ls[pre]);
		}else{
			ls[now]=ls[pre];
			rs[now]=modify(mid+1,r,posa,posb,ida,idb,rs[pre]);
		}
		return now;
	}

	void unite(int a,int b){
		tot++;
		int faa=fin(a),fab=fin(b);  //faa，fab表示主席树id
		int posa=point[faa],posb=point[fab];   //posa,pob表示节点编号
		if(posa!=posb){
			if(dep[faa]<=dep[fab]) roo[tot]=modify(1,n,posa,posb,faa,fab,roo[tot-1]);
			else roo[tot]=modify(1,n,posb,posa,fab,faa,roo[tot-1]);
		}else roo[tot]=roo[tot-1];
	}

	void go_old(int old){
		tot++;
		roo[tot]=roo[old];
		return;
	}

	int query(int l,int r,int pos,int id)  {//根据数组下标找到id
		if(l==r) return id;
		int mid=(l+r)>>1;
		if(pos<=mid) return query(l,mid,pos,ls[id]);
		return query(mid+1,r,pos,rs[id]);
	}

	int same(int a,int b){
		int faa=fin(a),fab=fin(b);
		return point[faa]==point[fab]?1:0;
	}

	int fin(int pos){
		int fath=query(1,n,pos,roo[tot-1]);
		if(point[fath]==pos) return fath;
		return fin(point[fath]);
	}
}tree;

int main()
{
	scanf("%d %d",&n,&m);
	tree.roo[0]=tree.build(1,n);

	int ans=0;
	for(int i=1;i<=m;i++){
		scanf("%d",&type);
		if(type==1){
			scanf("%d %d",&a,&b);a^=ans;b^=ans;
			tree.unite(a,b);
		}else if(type==2){
			scanf("%d",&old);old^=ans;
			tree.go_old(old);
		}else{
			scanf("%d %d",&a,&b);a^=ans;b^=ans;
			tree.roo[i]=tree.roo[i-1];
			tree.tot++;
			ans=tree.same(a,b);
			printf("%d\n",ans);
		}
	}
}