//hdu4358:统计所有子树颜色种数
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;
const int maxn=100005;

//题目数据
int t,n,u,v,q,k,a[maxn],b[maxn],ans[maxn],cnt[maxn],sum,m;
vector<int> vec[maxn];
//树剖用
int tot=0,siz[maxn],son[maxn];
int vis[maxn];

void dfs1(int cur,int fath,int he){ //dfs(root,0,1)
    siz[cur]=1;
    for(int i=0;i<vec[cur].size();i++){
        if(vec[cur][i]!=fath){
            dfs1(vec[cur][i],cur,he+1);
            siz[cur]+=siz[vec[cur][i]];
            if(siz[vec[cur][i]]>siz[son[cur]]) son[cur]=vec[cur][i];
        }
    }
}

void calc(int cur,int fa,int val) {
    if(cnt[a[cur]]==k) sum--;
    cnt[a[cur]]+=val;
    if(cnt[a[cur]]==k) sum++;
    for(int i=0;i<vec[cur].size();i++){
        if(vec[cur][i]!=fa&&!vis[vec[cur][i]]){  //!vis[vec[cur][i]]表示不计算重儿子的贡献，因为已经计算过
            calc(vec[cur][i],cur,val);
        }
    }
}

void dfs(int cur,int fa,bool keep) {//keep表示以当前节点为根节点的子树的贡献是否保留
    for(int i=0;i<vec[cur].size();i++){
        if(vec[cur][i]!=fa&&vec[cur][i]!=son[cur])
            dfs(vec[cur][i],cur,0);//计算轻链的结果，并且不保存
    }
    if(son[cur]) dfs(son[cur],cur,1),vis[son[cur]]=1; //计算重儿子贡献，并打上标记，防止下一次calc的时候重复计算
    calc(cur,fa,1);//计算当前节点和所有以轻儿子为根节点的子树的贡献
    ans[cur]=sum;  //这里就计算好了整颗以当前节点为根节点的子树的贡献
    if(son[cur]) vis[son[cur]]=0;  //消除标记，防止对下一步的清空操作产生影响，因为如果当前节点是轻儿子的话，那么整颗以
 							//当前节点为根节点的子树的贡献都要清空，如果不把重儿子的标记去掉，那么以重儿子为根的
 							//子树的贡献就无法在下一步清空
    if(!keep) calc(cur,fa,-1);  //如果当前节点作为父节点的轻儿子，那么消除以当前节点为根节点的子树的影响
}

void init() {
    tot=0;sum=0;
    memset(son,0,sizeof(son));
    memset(cnt,0,sizeof(cnt));
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) vec[i].clear();
}

int main() {
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++){
        scanf("%d %d",&n,&k);init();
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
        sort(b+1,b+n+1);
        m=unique(b+1,b+n+1)-b-1;
        for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+m+1,a[i])-b;
        for(int i=1;i<n;i++){
            scanf("%d %d",&u,&v);
            vec[u].push_back(v);
            vec[v].push_back(u);
        }
        dfs1(1,0,1);
        dfs(1,0,0);
        scanf("%d",&q);
        printf("Case #%d:\n",cas);
        for(int i=1;i<=q;i++){
            scanf("%d",&u);
            printf("%d\n",ans[u]);
        }
        if(cas<t) printf("\n");
    }
}
