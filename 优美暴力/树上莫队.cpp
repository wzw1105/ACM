#include<bits/stdc++.h>

using namespace std;
const int maxn=40005;     //node_size
const int maxm=1e5+10;    //query_size
const int max_color=1e5+10; //color_size

namespace IO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 

    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){
        return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';
    } 

    template<typename T>
    inline bool read(T &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror) return false; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; return true;
    } 
};
using namespace IO;

vector<int> vec[maxn];

//LCA数据
int id[2*maxn],num[maxn],dep[2*maxn],dp[2*maxn][20],tot,Log[2*maxn];
//树上莫队数据
int id1[2*maxn],num1[maxn],tot1,st[maxn],en[maxn];
//树上莫队欧拉序与lca用的欧拉序有点不同
void dfs(int cur,int h,int fa) {
    id[++tot]=cur;dep[tot]=h;num[cur]=tot;  //lca
    id1[++tot1]=cur;st[cur]=tot1;           //mo_dui
    for(int i=0;i<vec[cur].size();i++){
        if(vec[cur][i]!=fa){
            dfs(vec[cur][i],h+1,cur);
            id[++tot]=cur;dep[tot]=h;       //lca
        }
    }
    id1[++tot1]=cur;en[cur]=tot1;           //mo_dui
}

void init_st() {
    for(int i=1;i<=tot;i++) dp[i][0]=id[i];
    for(int j=1;(1<<j)<=tot;j++){
        for(int i=1;i+(1<<j)-1<=tot;i++){
            if(dep[num[dp[i][j-1]]]<dep[num[dp[i+(1<<(j-1))][j-1]]]) 
                dp[i][j]=dp[i][j-1];
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
    tot=tot1=0;
    dfs(root_,0,0);
    init_st();
    Log[0]=-1;
    for(int i=1;i<2*maxn;i++) Log[i]=Log[i>>1]+1;
}

int n,m,u,v,block_size,res,a[maxn],b[maxn];
int block[2*maxn],have[max_color],used[max_color],ans[maxm];
struct query{
    int l,r,id,lca; //id:id-th query lca:LCA(u,v)(if LCA!=u and v)else:-1
    query(int a=0,int b=0,int c=0,int d=-1){
        l=a;r=b;id=c;lca=d;
    }
    friend bool operator<(const query&a,const query&b){
        return block[a.l]==block[b.l]?a.r<b.r:block[a.l]<block[b.l];
    }
}q[maxm];

void init_query() {
    for(int i=1;i<=m;i++) {
        if(st[q[i].l]>st[q[i].r]) swap(q[i].l,q[i].r);
        int _lca=lca(q[i].l,q[i].r);
        if(_lca==q[i].l) q[i]=query(st[q[i].l],st[q[i].r],q[i].id,-1);
        else q[i]=query(en[q[i].l],st[q[i].r],q[i].id,_lca);
    }
    sort(q+1,q+m+1);
}

void init_modui() {
    res=0;
    memset(have,0,sizeof(have));
    memset(used,0,sizeof(have));
}

void add(int color) {if(++have[color]==1) res++;}
void del(int color) {if(--have[color]==0) res--;}
void update(int pos) {
    if(used[pos]) del(a[pos]);
    else add(a[pos]);
    used[pos]^=1;
}
void mo_dui() {
    int l=1,r=0;
    for(int i=1;i<=m;i++) {
        while(l<q[i].l) update(id1[l++]);
        while(l>q[i].l) update(id1[--l]);
        while(r<q[i].r) update(id1[++r]);
        while(r>q[i].r) update(id1[r--]);

        if(q[i].lca!=-1) update(q[i].lca);
        ans[q[i].id]=res;
        if(q[i].lca!=-1) update(q[i].lca);
    }
}

int main() {
    read(n);read(m);block_size=sqrt(n);
    for(int i=1;i<=n;i++) read(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);int total=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+total+1,a[i])-b;
    for(int i=1;i<=2*n;i++) block[i]=i/block_size;
    for(int i=1;i<n;i++) {
        read(u);read(v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i=1;i<=m;i++) {
        read(u);read(v);
        q[i]=query(u,v,i);
    }
    init_lca(1,n);
    init_query();
    init_modui();

    mo_dui();
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}

