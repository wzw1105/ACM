/*
节点编号[0,n-1]
*/
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
const int maxn=1001;
struct ed{int x,y,w;}edge[maxn];
int vis[maxn],id[maxn],in[maxn],pre[maxn];
int zhuLiu(int root,int n,int m){
    int res=0;
    while(true){
        for(int i=0;i<n;i++) in[i]=inf;
        for(int i=0;i<m;i++){
            int x=edge[i].x,y=edge[i].y;
            if(edge[i].w<in[y] && x!=y) pre[y]=x,in[y]=edge[i].w;
        }
        for(int i=0;i<n;i++){
            if(i==root) continue;
            if(in[i]==inf) return -1;
        }
        int cnt=0;in[root]=0;
        memset(id,-1,sizeof(id));
        memset(vis,-1,sizeof(vis));
        for(int i=0;i<n;i++){
            res+=in[i];int y=i;
            while(vis[y]!=i && id[y]==-1 && y!=root) vis[y]=i,y=pre[y];
            if(y!=root && id[y]==-1){
                for(int x=pre[y];x!=y;x=pre[x]) id[x]=cnt;
                id[y]=cnt++;
            }
        }
        if(cnt==0) break;
        for(int i=0;i<n;i++) if(id[i]==-1) id[i]=cnt++;
        for(int i=0;i<m;i++){
            int x=edge[i].x,y=edge[i].y;
            edge[i].x=id[x],edge[i].y=id[y];
            if(id[x]!=id[y]) edge[i].w-=in[y];
        }
        n=cnt,root=id[root];
    }
    return res;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].w);
        if(edge[i].x==edge[i].y) edge[i].w=inf;
    }
    int res=zhuLiu(0,n,m);
    if(res==-1) printf("No\n");
    else printf("%d\n",res);
    return 0;
}