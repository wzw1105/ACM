#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;

int n,q,l,r,opt;
long long a[maxn],mark[maxn],minn[maxn],maxx[maxn];

void pushup(int id) {
	minn[id]=min(minn[id<<1],minn[id<<1|1]);
	maxx[id]=max(maxx[id<<1],maxx[id<<1|1]);
}

void down(int id) {
	mark[id<<1]+=mark[id];mark[id<<1|1]+=mark[id];
	minn[id<<1]+=mark[id];minn[id<<1|1]+=mark[id];
	maxx[id<<1]+=mark[id];maxx[id<<1|1]+=mark[id];
	mark[id]=0;
}

void build(int id,int l,int r) {
	mark[id]=minn[id]=maxx[id]=0;
	if(l==r) {minn[id]=maxx[id]=a[l];return;}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);build(id<<1|1,mid+1,r);
	pushup(id);
}

void update(int id,int L,int R,int l,int r,long long add) {
	if(l<=L&&R<=r) {
		mark[id]+=add;minn[id]+=add;maxx[id]+=add;
		return;
	}
	if(mark[id]!=0) down(id);int mid=(L+R)>>1;
	if(l<=mid) update(id<<1,L,mid,l,r,add);
	if(r>mid) update(id<<1|1,mid+1,R,l,r,add);
	pushup(id);
}

long long query_max(int id,int L,int R,int l,int r) {
	if(l<=L&&R<=r) return maxx[id];long long res=-0x3f3f3f3f3f3f3f3f;
	if(mark[id]!=0) down(id);int mid=(L+R)>>1;
	if(l<=mid) res=max(res,query_max(id<<1,L,mid,l,r));
	if(r>mid) res=max(res,query_max(id<<1|1,mid+1,R,l,r));
	return res;
}

long long query_min(int id,int L,int R,int l,int r) {
	if(l<=L&&R<=r) return minn[id];long long res=0x3f3f3f3f3f3f3f3f;
	if(mark[id]!=0) down(id);int mid=(L+R)>>1;
	if(l<=mid) res=min(res,query_min(id<<1,L,mid,l,r));
	if(r>mid) res=min(res,query_min(id<<1|1,mid+1,R,l,r));
	return res;
}

int main() {
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,1,n);
	while(q--){
		scanf("%d %d %d",&opt,&l,&r);
		if(!opt) printf("%lld\n",query_min(1,1,n,l,r));
		else printf("%lld\n",query_max(1,1,n,l,r));
	}
}

