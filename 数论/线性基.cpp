#include<bits/stdc++.h>

using namespace std;

struct Linear_Basis{
	long long a[65],b[65];int tot;
	Linear_Basis(){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		tot=0;
	}
	bool insert(long long k){
		for(int i=62;i>=0;i--){
			if(k&(1LL<<i)){
				if(!a[i]) {a[i]=k;break;}
				else k^=a[i];
			}
		}
		return k>0;
	}
	long long query_max(){
		long long ans=0;
		for(int i=62;i>=0;i--) if(a[i]&&(a[i]^ans)>ans) ans^=a[i];
		return ans;
	}
	long long query_min(){
		long long ans=0;
		for(int i=0;i<=62;i++) if(a[i]) return a[i];
		return 0;
	}
	void rebuild() {
        for(int i=62;i>=0;i--) for(int j=i-1;j>=0;j--) if(a[i]&(1LL<<j)) a[i]^=a[j];
        for(int i=0;i<=62;i++) if(a[i]) b[tot++]=a[i];
    }
    long long query(long long k) {
        long long ret=0;
        if (k>=(1LL<<tot)) return -1;
        for (int i=62;i>=0;i--) if(k&(1LL<<i)) ret^=b[i];
        return ret;
    }

	Linear_Basis merge(const Linear_Basis oth){
		Linear_Basis res=*this;
		for(int i=62;i>=0;i--) if(oth.a[i]) res.insert(oth.a[i]);
		return res;
	}
}lb;

int n;
long long a[55];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		lb.insert(a[i]);
	}
	long long t;lb.rebuild();
	while(~scanf("%lld",&t)) printf("%lld\n",lb.query(t));
	printf("%lld\n",lb.query_max());
}