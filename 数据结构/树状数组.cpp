struct bit{
	int s[maxn];
	int lowbit(int x) {return x&(-x);} 
	void add(int id,int val){
		for(int i=id;i<=n;i+=lowbit(i)) s[i]+=val; //注意这里的n,需要根据题目要求改
	}
	int query(int id){
		int ans=0;
		for(int i=id;i>=1;i-=lowbit(i)) ans+=s[i];
		return ans;
	}
	int sum(int l,int r) {return query(r)-query(l-1);}
	void clear() {memset(s,0,sizeof(s));}
};