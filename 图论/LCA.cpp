#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;
const int maxn = 300005;
vector<int> vec[maxn];

//无向树LCA 默认从节点1为根节点，有向树dfs的第一个参数改为root即可
int id[2*maxn],num[maxn],dep[2*maxn],dp[2*maxn][25],tot,Log[maxn];
void dfs(int cur,int h,int fa) {
    id[++tot]=cur;dep[tot]=h;num[cur]=tot;
    for(int i=0;i<vec[cur].size();i++){
        if(vec[cur][i]!=fa){
            dfs(vec[cur][i],h+1,cur);
            id[++tot]=cur;dep[tot]=h;
        }
    }
}

void st() {
    for(int i=1;i<=tot;i++) dp[i][0]=id[i];
    for(int j=1;(1<<j)<=tot;j++){
        for(int i=1;i+(1<<j)-1<=tot;i++){
            if(dep[num[dp[i][j-1]]]<dep[num[dp[i+(1<<(j-1))][j-1]]]) dp[i][j]=dp[i][j-1];
            else dp[i][j]=dp[i+(1<<(j-1))][j-1];
        }
    }
}

int lca(int u,int v) {
    int a=min(num[u],num[v]),b=max(num[u],num[v]),k=Log[b-a+1];
    int x=num[dp[a][k]],y=num[dp[b-(1<<k)+1][k]];
    return dep[x]<dep[y]?dp[a][k]:dp[b-(1<<k)+1][k];
}

void init_lca(int root_,int n) {//root_为树根,n为结点数
    memset(num,0,sizeof(num));
    tot=0;
    dfs(root_,0,0);
    st();
    Log[0]=-1;
    for(int i=1;i<maxn;i++) Log[i]=Log[i>>1]+1;
}

int n,q,u,v,son,fa;
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++){
        scanf("%d %d",&fa,&son);
        vec[fa].push_back(son);
        vec[son].push_back(fa);
    }
    init_lca(1,n);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++){
        scanf("%d %d", &u, &v);
        int ans = lca(u, v);
        printf("%d\n", ans);
    }

    for(int i=1;i<=n;i++) vec[i].clear();
}


