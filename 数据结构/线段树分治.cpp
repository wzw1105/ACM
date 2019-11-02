/*
LOJ121:动态图连通性
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=5e3+10;
const int maxm=5e5+10;

int n,m,ans[maxm];

struct operate{
    int opt,x,y;
    operate(int o=0,int a=0,int b=0) {
        opt=o;x=a;y=b;
    }
}o[maxm],sta[maxm];

namespace dsu{
    int fa[maxn],dep[maxn],tot;  //tot表示栈sta里的元素个数
    void init(int k) {
        tot=0;
        for(int i=1;i<=k;i++) fa[i]=i,dep[i]=0;
    }
    int find(int x) {return fa[x]==x?x:find(fa[x]);}
    void merge(int x,int y) {
        x=find(x),y=find(y);
        if(x==y) return;
        if(dep[x]>dep[y]) swap(x,y);
        if(dep[x]==dep[y]) dep[y]++;
        sta[++tot]=operate(0,x,y);  //注意栈中元素的构造函数,记录的是father
        fa[x]=y;
    }

    void undo(int id) {
        while(tot>id) {
            int x=sta[tot].x,y=sta[tot--].y;
            if(dep[y]==dep[x]+1) dep[y]--;
            fa[x]=x;
        }
    }
};
using namespace dsu;

namespace segment_tree{
    vector<operate> add[maxm<<2];
    void update(int id,int L,int R,int l,int r,int k) {
        if(L>=l&&R<=r) {add[id].push_back(o[k]);return;}
        int mid=(L+R)>>1;
        if(l<=mid) update(id<<1,L,mid,l,r,k);
        if(r>mid) update(id<<1|1,mid+1,R,l,r,k);
    }
    void work(int id,int L,int R) {
        int now=tot;
        for(int i=0;i<add[id].size();i++) merge(add[id][i].x,add[id][i].y);
        if(L==R) if(o[L].opt==2) ans[L]=(find(o[L].x)==find(o[L].y));
        else {
            int mid=(L+R)>>1;
            work(id<<1,L,mid);work(id<<1|1,mid+1,R);
        }
        undo(now); //叶子结点也要undo
    }
};
using namespace segment_tree;

int exist[maxn][maxn];
int main()
{
    scanf("%d %d",&n,&m);
    init(n);
    for(int i=1;i<=m;i++) {
        scanf("%d %d %d",&o[i].opt,&o[i].x,&o[i].y);
        if(o[i].opt==0) {
            if(exist[o[i].x][o[i].y]) continue;
            exist[o[i].x][o[i].y]=exist[o[i].y][o[i].x]=i;
        }else if(o[i].opt==1) {
            update(1,1,m,exist[o[i].x][o[i].y],i-1,i);
            exist[o[i].x][o[i].y]=exist[o[i].y][o[i].x]=0;
        }
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(exist[i][j]) {
        update(1,1,m,exist[i][j],m,exist[i][j]);
        exist[i][j]=exist[j][i]=0; 
    }
    work(1,1,m);
    for(int i=1;i<=m;i++) if(o[i].opt==2) printf(ans[i]?"Y\n":"N\n");
    return 0; 
}