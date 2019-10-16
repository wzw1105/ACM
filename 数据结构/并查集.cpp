struct dsu{
	int fa[maxn];
	dsu(int k){
		for(int i=1;i<=k;i++) fa[i]=i,rank[i]=0;
	}
	int fin(int k){
		return fa[k]==k?k:(fa[k]=fin(fa[k]));
	}
	
	void unite(int a,int b){
		int x=fin(a),y=fin(b);
		if(x==y) return;
		fa[x]=y;
	}
	
	bool same(int a,int b){
		return fin(a)==fin(b);
	}
};
