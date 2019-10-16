#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
const int maxn = 2e5+10;
const int maxm = 5e6+10;
int n, q, a[maxn], u, v, k;
//val:数组a离散化后的数组, tot:离散后的size roo:第i代的根结点编号
namespace president_tree{
    int sum[maxm], cnt, val[maxn], tot, ls[maxm], rs[maxm], roo[maxn];          
    inline void init() {cnt=0;}
    int build(int l, int r)   {
        int now = ++cnt;
        if(l == r) return now;
        int mid = (l + r) >> 1;
        ls[now] = build(l, mid);
        rs[now] = build(mid + 1, r);
        return now;
    }
    int modify(int l, int r, int loc, int pre) {                                          
        int now=++cnt;
        sum[now]=sum[pre]+1;
        if(l==r) return now;
        int mid=(l+r)>>1;
        if(loc<=mid){
            rs[now]=rs[pre];
            ls[now]=modify(l, mid, loc, ls[pre]);
        }else{
            ls[now]=ls[pre];
            rs[now]=modify(mid+1,r,loc,rs[pre]);
        }
        return now;
    }
    inline void build_tree(int a[],int n) {
        init();
        for(int i=1;i<=n;i++) val[i]=a[i];
        sort(val+1,val+n+1);
        tot=unique(val+1,val+n+1)-val-1;
        roo[0]=build(1,tot);
        for(int i=1;i<=n;i++) {
            int loc=lower_bound(val+1,val+tot+1,a[i])-val;
            roo[i]=modify(1,tot,loc,roo[i-1]);
        }
    }
    //查询区间小于等于k的数量,a,b为区间对应的节点编号
    inline int query(int l, int r, int k, int a, int b) {
        if(l==r) return val[l]<=k?sum[b]-sum[a]:0;
        if(l>r) return 0;
        int mid=(l+r)>>1;
        if(k>val[mid]) return sum[ls[b]]-sum[ls[a]]+query(mid+1,r,k,rs[a],rs[b]);
        return query(l,mid,k,ls[a],ls[b]);
    }
    //查询区间第k大
    inline int query_kth(int l, int r, int k, int a, int b) {
        if(l == r) return l;
        int s = sum[ls[b]] - sum[ls[a]];
        int mid = (l + r) >> 1;
        if(s >= k) return query_kth(l, mid, k, ls[a], ls[b]);
        return query_kth(mid + 1, r, k - s, rs[a], rs[b]);
    }
}using namespace president_tree;

int main()
{
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
    build_tree(a,n);
    for(int i = 1; i <= q; i++){
        scanf("%d %d %d", &u, &v, &k);
        printf("%d\n", query(1, tot, k, roo[u - 1], roo[v]));
    }
}