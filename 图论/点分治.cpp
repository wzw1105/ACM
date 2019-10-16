/*
POJ1741:求树上dis(u,v)<=k的点对数
*/
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=2e5+10;
int n,k;
namespace point_divide_and_conquer{
    int tot,head[maxn],siz[maxn],dis[maxn],root,min_son,num; //min_son记录当前最小的 最大儿子size
    bool vis[maxn];
    struct ed{int v,w,next;}edge[2*maxn];
    inline void init(int n) {
        tot=0;
        for(int i=1;i<=n;i++) head[i]=0,vis[i]=false;
    }
    inline void add_edge(int u,int v,int w) {
        edge[++tot]=ed{v,w,head[u]};
        head[u]=tot;
    }
    inline void dfs_size(int cur,int fa) {
        siz[cur]=1;
        for(int i=head[cur];i;i=edge[i].next) {
            if(edge[i].v!=fa && !vis[edge[i].v]) {
                dfs_size(edge[i].v,cur);
                siz[cur]+=siz[edge[i].v];
            }
        }
    }
    inline void dfs_root(int cur,int fa,int all) {  //all表示这个联通块的大小
        int max_son=all-siz[cur];
        for(int i=head[cur];i;i=edge[i].next) {
            if(edge[i].v!=fa && !vis[edge[i].v]) {
                max_son=max(max_son,siz[edge[i].v]);
                dfs_root(edge[i].v,cur,all);
            }
        }
        if(max_son<min_son) min_son=max_son,root=cur;
    }
    inline void dfs_roote(int cur,int fa,int d) {
        dis[++num]=d;
        for(int i=head[cur];i;i=edge[i].next) {
            if(edge[i].v!=fa && !vis[edge[i].v]) {
                dfs_roote(edge[i].v,cur,d+edge[i].w);
            }
        }
    }
    inline long long calc(int cur,int fa,int d) {
        num=0;
        dfs_roote(cur,fa,d);
        sort(dis+1,dis+num+1);
        long long ans=0;
        int i=1,j=num;
        while(i<j) {
            while(i<j && dis[i]+dis[j]>k) j--;
            ans+=(j-i);
            i++;
        }
        return ans;
    }
    inline long long solve(int cur) {
        min_son=0x3f3f3f3f;
        dfs_size(cur,0);
        dfs_root(cur,0,siz[cur]);
        vis[root]=true;
        long long ans=calc(root,0,0);
        for(int i=head[root];i;i=edge[i].next) if(!vis[edge[i].v]) ans-=calc(edge[i].v,0,edge[i].w);
        for(int i=head[root];i;i=edge[i].next) if(!vis[edge[i].v]) ans+=solve(edge[i].v);
        return ans;
    }
}
using namespace point_divide_and_conquer;
int main() {
    while(~scanf("%d %d",&n,&k) && n) {
        init(n);
        for(int i=1,u,v,w;i<n;i++) {
            scanf("%d %d %d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        
        printf("%lld\n",solve(1));
    }
}