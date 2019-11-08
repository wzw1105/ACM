/*
hdu3040: 手写优先队列优化
*/

#include<bits/stdc++.h>
using namespace std;
const int maxn=300005;
const int maxm=1000005;
#define inf 0x3f3f3f3f

struct edge{int u,v,w,next;}e[maxm];
int n,m,head[maxn],tot;
long long dis[maxn];
void add_edge(int u,int v,int w) {e[++tot]=edge{u,v,w,head[u]};head[u]=tot;}
void clear(int n)  {for(int i=1;i<=n;i++) head[i]=0;tot=0;}

namespace priority_que{
    //id[i]:图节点i在堆中的id node[i]:堆中编号为i的图节点编号 val[i]:堆中编号为i的权值 siz:堆中总节点数
    int id[maxn],node[maxn],val[maxn],siz;

    //函数参数u,v均为堆中节点编号，而不是图上节点编号
    void swap_(int u,int v) {swap(node[u],node[v]),swap(id[node[u]],id[node[v]]),swap(val[u],val[v]);} 
    void down(int u) {
        int nxt=u;
        if((u<<1) <= siz && val[(u<<1)] < val[nxt]) nxt=u<<1;
        if((u<<1|1) <= siz && val[(u<<1|1)] < val[nxt]) nxt=u<<1|1;
        if(nxt!=u) swap_(u,nxt),down(nxt);
    }
    void up(int u) {
        while(u/2 && val[u/2] > val[u]) {
            swap_(u,u/2);
            u/=2;
        }
    }
    void modify(int u,int new_val) {
        val[u]=new_val;
        down(u),up(u);
    }
    int top_() {return val[1];}
    int pop_() {
        int res=val[1];
        swap_(1,siz--),down(1);
        return res;
    }
}
using namespace priority_que;

long long dijkstra(int s,int n_) {
    for(int i=1;i<=n_;i++) val[i]=inf,id[i]=node[i]=i;
    val[id[s]]=0,siz=n_;
    while(siz){
        int cur=node[1],d=val[1];
        pop_();
        for(int i=head[cur];i;i=e[i].next) {
            if(val[id[e[i].v]] > d + e[i].w) {
                modify(id[e[i].v],d + e[i].w);
            }
        }
    }
    return val[id[n]]==inf?-1:val[id[n]];
}

int c[maxn],l[maxn],r[maxn],C;
vector<int> belong[maxn];
int main() {
    int t;scanf("%d",&t);
    for(int cas=1;cas<=t;cas++) {
        scanf("%d %d %d",&n,&m,&C);
        for(int i=1;i<=n;i++) scanf("%d",&c[i]),belong[c[i]].push_back(i);
        for(int i=1,u,v,w;i<=m;i++){
            scanf("%d %d %d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        int tot_node=n;
        for(int i=1;i<=n;i++) {
            if(belong[i].size()) {
                l[i]=++tot_node,r[i]=++tot_node;
                for(int j=0;j<belong[i].size();j++) {
                    add_edge(l[i],belong[i][j],0),add_edge(belong[i][j],r[i],0);
                }    
            }else l[i]=r[i]=-1;
        }
        for(int i=1;i<=n;i++) {
            if(i>1 && l[i-1]!=-1 && r[i]!=-1) add_edge(r[i],l[i-1],C);
            if(i<n && l[i+1]!=-1 && r[i]!=-1) add_edge(r[i],l[i+1],C);
        }

        printf("Case #%d: %lld\n",cas,dijkstra(1,tot_node));
        for(int i=1;i<=n;i++) belong[i].clear();
        clear(tot_node);        
    }
}