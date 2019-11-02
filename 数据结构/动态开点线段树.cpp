#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn=50000+10;

struct dynamic_segment_tree{
	int tot;
	struct node{
		int maxx,mark;
		int ls,rs,sum;
		node(int a=0,int b=0,int c=0,int d=0,int e=0){
			maxx=a;sum=b;mark=c;ls=d;rs=e;
		}
	}tree[20*maxn];
	dynamic_segment_tree(){
		tot=1;
		memset(tree,0,sizeof(tree));
		tree[0].maxx=-2e9;
	}
	void init(){
		tot=1;
		memset(tree,0,sizeof(tree));
		tree[0].maxx=-2e9;
	}
	void pushup(int id){
		tree[id].maxx=max(tree[tree[id].ls].maxx,tree[tree[id].rs].maxx);
		tree[id].sum=tree[tree[id].ls].sum+tree[tree[id].rs].sum;
	}
	//单点更新
	void update(int l,int r,int k,int val,int id){
		if(l==r){
			tree[id].maxx=val;
			tree[id].sum=1;
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid){
			if(!tree[id].ls) tree[id].ls=++tot;
			update(l,mid,k,val,tree[id].ls);
		}else{
			if(!tree[id].rs) tree[id].rs=++tot;
			update(mid+1,r,k,val,tree[id].rs);
		}
		pushup(id);
	}
	int query(int l,int r,int le,int ri,int id){ //l,r区间端点，le,ri待查询区间
		if(le>ri) return -2e9;
		int ans=-2e9;
		if(l>=le&&r<=ri) return tree[id].maxx;
		int mid=(l+r)>>1;
		if(le<=mid&&tree[id].ls) ans=max(ans,query(l,mid,le,ri,tree[id].ls));
		if(ri>mid&&tree[id].rs) ans=max(ans,query(mid+1,r,le,ri,tree[id].rs));
		return ans;
	}
	int sum(int l,int r,int le,int ri,int id){
		if(le>ri) return 0;
		int ans=0;
		if(le<=l&&ri>=r) return tree[id].sum;
		int mid=(l+r)>>1;
		if(le<=mid&&tree[id].ls) ans+=sum(l,mid,le,ri,tree[id].ls);
		if(ri>mid&&tree[id].rs) ans+=sum(mid+1,r,le,ri,tree[id].rs);
		return ans;	
	}
}data;

int n,m;
int a,b,year,water,L=-1e9,R=1e9;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&year,&water);
		data.update(L,R,year,water,1);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d",&a,&b);
		if(b<a) {printf("false\n");continue;}
		int le=data.sum(L,R,a,a,1),ri=data.sum(L,R,b,b,1),mid=data.sum(L,R,a+1,b-1,1);
		int c=data.query(L,R,a,a,1),d=data.query(L,R,b,b,1),e=data.query(L,R,a+1,b-1,1);
		if(le&&ri){
			if(d<=c){
				if(mid==b-a-1&&e<d) printf("true\n");
				else if(e<d) printf("maybe\n");
				else printf("false\n"); 
			}else printf("false\n");
		}else if(le){
			if(e<c) printf("maybe\n");
			else printf("false\n");
		}else if(ri){
			if(e<d) printf("maybe\n");
			else printf("false\n");
		}else printf("maybe\n");
	}
}