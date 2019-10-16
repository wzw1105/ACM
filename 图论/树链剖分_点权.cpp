#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;

vector<int> vec[maxn];
int n,m,u[maxn],v[maxn],w[maxn],val,a[maxn],x,y;
char opt[20];

// 树剖用
struct ed{int v,w,next;}edge[2*maxn];
int h[maxn],fa[maxn],top[maxn],id[maxn],son[maxn],siz[maxn],rk[maxn],tot,head[maxn],cnt;
/*
id[i]:节点i的新编号
rk[i]:新编号为i的原节点编号
top[i]:节点i所在重链的深度最低的节点
h[i]:节点i的深度
siz[i]:节点i为根的子树size
*/

namespace segment_tree{
    int sum[maxn<<2],mark[maxn<<2],maxx[maxn<<2];
    inline void pushup(int id){
        sum[id]=sum[id<<1]+sum[id<<1|1];
        maxx[id]=max(maxx[id<<1],maxx[id<<1|1]);
    }
    inline void build(int id,int L,int R){
        mark[id]=0;
        if(L==R) {sum[id]=maxx[id]=a[rk[L]];return;}
        int mid=(L+R)>>1;
        build(id<<1,L,mid);
        build(id<<1|1,mid+1,R);
        pushup(id);
    }
    inline void down(int id,int L,int R){
        int mid=(L+R)>>1;
        mark[id<<1]=(mark[id<<1]+mark[id]);
        mark[id<<1|1]=(mark[id<<1|1]+mark[id]);
        sum[id<<1]=(sum[id<<1]+(mid-L+1)*mark[id]); //注意爆int
        sum[id<<1|1]=(sum[id<<1|1]+(R-mid)*mark[id]);
        maxx[id<<1]+=mark[id];
        maxx[id<<1|1]+=mark[id];
        mark[id]=0;
    }
    //单点修改
    inline void update(int id,int L,int R,int pos,int val){
        if(L==R) {
            sum[id]=maxx[id]=val;
            return;
        }
        if(mark[id]) down(id,L,R);
        int mid=(L+R)>>1;
        if(pos<=mid) update(id<<1,L,mid,pos,val);
        else update(id<<1|1,mid+1,R,pos,val);
        pushup(id);
    }

    //区间更新
    inline void modify(int id,int L,int R,int l,int r,int add){
        if(l<=L&&r>=R){
            mark[id]=(mark[id]+add);
            sum[id]=(sum[id]+add*(R-L+1));
            return;
        }
        if(mark[id]) down(id,L,R);
        int mid=(L+R)>>1;
        if(l<=mid) modify(id<<1,L,mid,l,r,add);
        if(r>mid) modify(id<<1|1,mid+1,R,l,r,add);
        pushup(id);
    }

    //区间和
    inline int query_sum(int id,int L,int R,int l,int r){
        int ans=0;
        if(l<=L&&r>=R) return sum[id];
        if(mark[id]) down(id,L,R);
        int mid=(L+R)>>1;
        if(l<=mid) ans=(ans+query_sum(id<<1,L,mid,l,r));
        if(r>mid) ans=(ans+query_sum(id<<1|1,mid+1,R,l,r));
        return ans;
    }

    //区间最大值
    inline int query_max(int id,int L,int R,int l,int r){
        //cout <<L<<' ' <<R<<endl;
        int ans=-1e9;
        if(l<=L&&r>=R) return maxx[id];
        if(mark[id]) down(id,L,R);
        int mid=(L+R)>>1;
        if(l<=mid) ans=max(ans,query_max(id<<1,L,mid,l,r));
        if(r>mid) ans=max(ans,query_max(id<<1|1,mid+1,R,l,r));
        return ans; 
    }
}
using namespace segment_tree;

/*
dfs1(root,0,1):统计father,子树size,重儿子son[]，以及高度信息
dfs2(1,1):统计dfs的顺序进行标号，也就是说重链节点标号连续，然后统计每个节点所在重链的高度最低的节点
*/

namespace tree{
    inline void init(int n){
        cnt=tot=0;
        for(int i=1;i<=n;i++) son[i]=head[i]=0;
    }
    inline void add_edge(int u,int v,int w) {
        edge[++cnt]=ed{v,w,head[u]};
        head[u]=cnt;
    }

    inline void dfs1(int cur,int fath,int he){ //dfs(root,0,1)
        h[cur]=he;fa[cur]=fath;siz[cur]=1;
        for(int i=head[cur];i;i=edge[i].next){
            if(edge[i].v!=fath){
                dfs1(edge[i].v,cur,he+1);
                siz[cur]+=siz[edge[i].v];
                if(siz[edge[i].v]>siz[son[cur]]) son[cur]=edge[i].v;
            }
        }
    }
    inline void dfs2(int cur,int fath,int topp){ //dfs2(root,0,root)
        id[cur]=++tot;rk[tot]=cur;top[cur]=topp;
        if(son[cur]) dfs2(son[cur],cur,topp);
        for(int i=head[cur];i;i=edge[i].next){
            if(edge[i].v!=fath&&edge[i].v!=son[cur]){
                dfs2(edge[i].v,cur,edge[i].v);
            }
        }
    }
    inline void build() {dfs1(1,0,1);dfs2(1,0,1);segment_tree::build(1,1,n);}

    //区间和
    /*
    对于链上的一些修改查询操作：选择topx的height低的跳，目的地就是两个点跳到同一条重链上;
    */
    inline int query_sum(int x,int y){
        int topx=top[x],topy=top[y];int ans=0;
        while(topx!=topy){
            if(h[topx]>=h[topy]){
                ans=(ans+segment_tree::query_sum(1,1,n,id[topx],id[x]));
                x=fa[topx],topx=top[x];
            }else{
                ans=(ans+segment_tree::query_sum(1,1,n,id[topy],id[y]));
                y=fa[topy],topy=top[y];
            }
        }
        ans=(ans+segment_tree::query_sum(1,1,n,min(id[x],id[y]),max(id[x],id[y])));
        return ans;
    }

    //区间最大值
    inline int query_max(int x,int y){
        int topx=top[x],topy=top[y];int ans=-1e9;
        while(topx!=topy){
            
            if(h[topx]>=h[topy]){
                ans=max(ans,segment_tree::query_max(1,1,n,id[topx],id[x]));
                x=fa[topx],topx=top[x];
            }else{
                ans=max(ans,segment_tree::query_max(1,1,n,id[topy],id[y]));
                y=fa[topy],topy=top[y];
            }
        } 
        ans=max(ans,segment_tree::query_max(1,1,n,min(id[x],id[y]),max(id[x],id[y])));
        return ans;
    }


    //单点修改
    inline void update(int x,int val){
        segment_tree::update(1,1,n,id[x],val);
    }

    //区间更新
    inline void modify(int x,int y,int add){
        int topx=top[x],topy=top[y];
        while(topx!=topy){
            if(h[topx]>=h[topy]){
                segment_tree::modify(1,1,n,id[topx],id[x],add);
                x=fa[topx],topx=top[x];
            }else{
                
                segment_tree::modify(1,1,n,id[topy],id[y],add);
                y=fa[topy],topy=top[y];
            }
        }
        segment_tree::modify(1,1,n,min(id[x],id[y]),max(id[x],id[y]),add);
    }

    //子树所有节点加
    inline void update_son_add(int x,int add){
        segment_tree::modify(1,1,n,id[x],id[x]+siz[x]-1,add);
    }
    //子树所有节点权值和
    inline int query_son_sum(int u){
        return segment_tree::query_sum(1,1,n,id[u],id[u]+siz[u]-1);
    }
    //子树所有节点权值最大值
    inline int query_son_max(int u){
        return segment_tree::query_max(1,1,n,id[u],id[u]+siz[u]-1);
    }

    inline void debug(){
        printf("son[]: "); for(int i=1;i<=n;i++) printf("%d%c",son[i],i==n?'\n':' ');
        printf("id[]:  ");for(int i=1;i<=n;i++) printf("%d%c",id[i],i==n?'\n':' ');
    }
}
using namespace tree;


int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d %d",&u[i],&v[i]);
        add_edge(u[i],v[i],w[i]);
        add_edge(v[i],u[i],w[i]);
    }
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);build();
    for(int i=1;i<=m;i++){
        scanf("%s %d %d",opt+1,&x,&y);
        if(opt[1]=='C') update(x,y);
        else if(opt[1]=='Q'&&opt[2]=='M') printf("%d\n",query_max(x,y));
        else printf("%d\n",query_sum(x,y));
    }
}