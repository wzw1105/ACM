#include<bits/stdc++.h>

using namespace std;
//欧拉通路与欧拉回路：基本要求：图联通
//有向图：
  //欧拉通路：所有节点入度=出度，或者只有一个节点入度比出度大1，一个节点出度比入度大一
  //欧拉回路：所有节点入度=出度
//无向图：
  //欧拉通路：有0个或两个度数为奇数的节点
  //欧拉回路：所有节点度数为偶数

const int maxn=100005;
int u,v,m,n,cnt[maxn],in[maxn],out[maxn];
vector<int> vec[maxn],vec1[maxn];
int vis1[maxn],vis[maxn];

struct dsu{
   int fa[maxn],rank[maxn],cnt[maxn];
   void init(int k){
       for(int i=1;i<=k;i++) fa[i]=i,rank[i]=0;
    memset(cnt,0,sizeof(cnt));
  }
  int fin(int k){
    return fa[k]==k?k:(fa[k]=fin(fa[k]));
  }
  
  void unite(int a,int b){
    int x=fin(a),y=fin(b);
    if(x==y) return;
    if(rank[x]<rank[y]) 
    fa[x]=y;
    else{
      fa[y]=x;
      if(rank[x]==rank[y]) rank[x]++;
    }
  }
  
  bool same(int a,int b){
    return fin(a)==fin(b);
  }

  bool connect(){
    for(int i=1;i<=n;i++) cnt[fin(i)]++;
    int res=0;
    for(int i=1;i<=n;i++) if(cnt[i]) res++;
    return res==1;
  }
}tree;


void init()
{
  for(int i=1;i<=n;i++) {vec[i].clear(),vec1[i].clear();}
  tree.init(n);
  memset(cnt,0,sizeof(cnt));
  memset(in,0,sizeof(in));
  memset(out,0,sizeof(out));
}

int main()
{
  int t;scanf("%d",&t);
  while(t--){
    scanf("%d %d",&n,&m);
    init();
    for(int i=1;i<=m;i++) {
      scanf("%d %d",&u,&v);
      vec[u].push_back(v);
      vec[v].push_back(u);
      cnt[u]++;cnt[v]++;
      tree.unite(u,v);

      vec1[u].push_back(v);
      out[u]++;in[v]++;
    }

    bool flag1=true,flag2=true;
    if(!tree.connect()) flag1=flag2=false;

    int odd=0;
    for(int i=1;i<=n;i++) if(cnt[i]%2) odd++;
    if(!(odd==0||odd==2)) flag1=false;

    int num=0;
    for(int i=1;i<=n;i++) if(in[i]!=out[i]) num++;
    if(num!=0&&num!=2) flag2=false;
    else if(num==2){
      int a=0,b=0;
      for(int i=1;i<=n;i++){
        if(in[i]-out[i]==1) a++;
        else if(out[i]-in[i]==1) b++;
      }
      if(!(a==1&&b==1)) flag2=false;
    }
    if(flag1) printf("Yes "); //无向图
    else printf("No ");

    if(flag2) printf("Yes\n");  //有向图
    else printf("No\n");
  }
}
