/*POJ3468
1. 区间加值
2. 区间sum查询
*/

#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;
const int maxn=2e5+10;
const int smaxn=5005;
int n,q;

namespace blocking{
    int tot,belong[maxn],siz[smaxn],block;  //分块基本数据
    long long v[maxn],sum[maxn],mark[maxn];                //解题数据
    void init(int n) {
        block=(int)sqrt((double)n);
        tot=n%block?(n/block+1):(n/block);
        for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;
        for(int i=1;i<=tot;i++) siz[i]=(min(i*block,n)-(i-1)*block);
    }
    void add(int l,int r,long long val) {
        if(belong[r]-belong[l]<=1) {
            for(int i=l;i<=r;i++) {
                sum[belong[i]]+=val;
                v[i]+=val;
            }
            return;
        }
        for(int i=l;i<=belong[l]*block;i++) sum[belong[i]]+=val,v[i]+=val;
        for(int i=belong[l]+1;i<=belong[r]-1;i++) mark[i]+=val,sum[i]+=block*val;
        for(int i=(belong[r]-1)*block+1;i<=r;i++) sum[belong[i]]+=val,v[i]+=val;
    }

    long long query(int l,int r) {
        long long ans=0;
        if(belong[r]-belong[l]<=1) {
            for(int i=l;i<=r;i++) ans+=v[i]+mark[belong[i]];
            return ans;
        }
        for(int i=l;i<=belong[l]*block;i++) ans+=v[i]+mark[belong[i]];
        for(int i=belong[l]+1;i<=belong[r]-1;i++) ans+=sum[i];
        for(int i=(belong[r]-1)*block+1;i<=r;i++) ans+=v[i]+mark[belong[i]];
        return ans;
    }

    void debug() {
        printf("block= %d, tot= %d\n",block,tot);
        for(int i=1;i<=n;i++) printf("%d%c",belong[i],i==n?'\n':' ');
    }
}
using namespace blocking;
char opt[10];
int l,r,c,b[maxn];
int main()
{
    scanf("%d %d",&n,&q);init(n);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]),add(i,i,b[i]);
    while(q--) {
        scanf("%s",opt+1);
        if(opt[1]=='Q') {
            scanf("%d %d",&l,&r);
            printf("%lld\n",query(l,r));
        }else {
            scanf("%d %d %d",&l,&r,&c);
            add(l,r,c);
        }
    }
}