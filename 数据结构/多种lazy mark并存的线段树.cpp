/*hdu4578
1. 区间加一个给定值
2. 区间乘一个给定值
3. 区间赋值为同一个给定值
4. 求区间内的所有数的p次方的和 p<=3
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
const long long mod=10007;

namespace segment_tree{
    int add[maxn<<2],mult[maxn<<2],same[maxn<<2];
    long long ans[4][maxn<<2];

    inline void build(int id,int L,int R) {
        add[id]=mult[id]=same[id]=0;
        for(int i=1;i<=3;i++) ans[i][id]=0;
        if(L==R) return;
        int mid=(L+R)>>1;
        build(id<<1,L,mid);build(id<<1|1,mid+1,R);
    }
    inline void mark_same(int id,int val,int L,int R) {  //用val去更新id这个节点信息并打上标记,val相当于一个懒惰标记
        same[id]=val;mult[id]=add[id]=0;
        for(int i=1,j=same[id]*(R-L+1)%mod;i<=3;i++,j=j*same[id]%mod) ans[i][id]=j;
    }
    inline void mark_mult(int id,int val,int L,int R) {
        if(!mult[id]) mult[id]=val;
        else mult[id]=mult[id]*val%mod;
        add[id]=(add[id]*val)%mod;
        for(int i=1,j=val;i<=3;i++,j=j*val%mod) ans[i][id]=ans[i][id]*j%mod;
    }
    inline void mark_add(int id,int val,int L,int R) {
        add[id]=(add[id]+val)%mod;
        ans[3][id]=(ans[3][id]+3*val*ans[2][id]%mod+(3*val*val%mod)*ans[1][id]%mod+((1LL*val*val*val)%mod)*(R-L+1)%mod)%mod;
        ans[2][id]=(ans[2][id]+2*val*ans[1][id]%mod+(val*val%mod)*(R-L+1)%mod)%mod;
        ans[1][id]=(ans[1][id]+(R-L+1)*val%mod)%mod;
    }
    inline void push_down(int id,int L,int R) { /*same 操作一定是最最先出现的，因为same操作会给其他操作清空*/
        int mid=(L+R)>>1;
        if(same[id]) {
            mark_same(id<<1,same[id],L,mid);
            mark_same(id<<1|1,same[id],mid+1,R);
            same[id]=0;
        } 
        if(mult[id]) {
            mark_mult(id<<1,mult[id],L,mid);
            mark_mult(id<<1|1,mult[id],mid+1,R);
            mult[id]=0;
        }
        if(add[id]) {
            mark_add(id<<1,add[id],L,mid);
            mark_add(id<<1|1,add[id],mid+1,R);
            add[id]=0;
        }
    }
    inline void push_up(int id) {
        for(int i=1;i<=3;i++) ans[i][id]=(ans[i][id<<1]+ans[i][id<<1|1])%mod;
    }
    inline void update(int id,int L,int R,int l,int r,int x,int type) {
        if(L>=l&&R<=r) {
            if(type==1) mark_add(id,x,L,R);
            else if(type==2) mark_mult(id,x,L,R);
            else mark_same(id,x,L,R);
            return;
        }
        int mid=(L+R)>>1;push_down(id,L,R);
        if(l<=mid) update(id<<1,L,mid,l,r,x,type);
        if(r>mid) update(id<<1|1,mid+1,R,l,r,x,type);
        push_up(id);
    }
    inline int query(int id,int L,int R,int l,int r,int type) {
        int sum=0;
        if(L>=l&&R<=r) return ans[type][id];
        int mid=(L+R)>>1;push_down(id,L,R);
        if(l<=mid) sum=(sum+query(id<<1,L,mid,l,r,type))%mod;
        if(r>mid) sum=(sum+query(id<<1|1,mid+1,R,l,r,type))%mod;
        push_up(id);
        return sum;
    }
};
using namespace segment_tree;

int n,m,opt,l,r,x;
int main()
{
    while(~scanf("%d %d",&n,&m)&&(n+m)) {
        build(1,1,n);
        for(int i=1;i<=m;i++) {
            scanf("%d %d %d %d",&opt,&l,&r,&x);
            if(opt<=3) update(1,1,n,l,r,x,opt);
            else printf("%d\n",query(1,1,n,l,r,x));
        }
    }
}