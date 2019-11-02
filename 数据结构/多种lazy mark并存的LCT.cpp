/*
hdu5002:
1.删除边(x,y)，加边(a,b)，保证操作之后还是一棵树
2.改变路径(a->b)上的所有点权为x
3.将路径(a->b)上的所有点权增加x
4.找出路径(a->b) 之间所有点权的第二大(指绝对第二大)
*/
#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
#define inf 0x3f3f3f3f

namespace LCT{
    int ch[maxn][2],fa[maxn],mark[maxn];
    int val[maxn],f[maxn],s[maxn],cntf[maxn],cnts[maxn],lazy[maxn][2],siz[maxn];    //lazy第一维:update 第二维:add
    inline void init(int k) {
        for(int i=1;i<=k;i++) {
            ch[i][0]=ch[i][1]=fa[i]=mark[i]=val[i]=cntf[i]=cnts[i]=siz[i]=lazy[i][1]=0;
            f[i]=s[i]=-inf;
            lazy[i][0]=inf;
        }
    }
    inline bool not_root(int x) {return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
    inline int  dir(int x) {return ch[fa[x]][1]==x;}
    inline void mark_rev(int x) {swap(ch[x][0],ch[x][1]);mark[x]^=1;}        //将x这颗子树翻转
    inline void mark_upd(int x,int v) {
        val[x]=v;
        lazy[x][0]=v,lazy[x][1]=0;
        f[x]=v,cntf[x]=siz[x];
        s[x]=-inf,cnts[x]=0;
    }
    inline void mark_add(int x,int v) {
        val[x]+=v;
        lazy[x][1]+=v;
        f[x]+=v;
        if(s[x]!=-inf) s[x]+=v;
    }
    inline void push_down(int x) {
        if(mark[x]) {
            if(ch[x][0]) mark_rev(ch[x][0]);
            if(ch[x][1]) mark_rev(ch[x][1]); 
            mark[x]=0;
        }
        if(lazy[x][0]!=inf) {
            if(ch[x][0]) mark_upd(ch[x][0],lazy[x][0]);
            if(ch[x][1]) mark_upd(ch[x][1],lazy[x][0]);
            lazy[x][0]=inf;
        }
        if(lazy[x][1]) {
            if(ch[x][0]) mark_add(ch[x][0],lazy[x][1]);
            if(ch[x][1]) mark_add(ch[x][1],lazy[x][1]);
            lazy[x][1]=0;
        }
    }


    inline void maintain(int &fir,int &sec,int val) {//插入val维护最大次大值
        if(val>fir)               {sec=fir;fir=val;}
        else if(val>sec&&val<fir) {sec=val;}
    }
    inline void push_up(int x) {
        siz[x]=1;
        int fir=val[x],sec=-inf;
        if(ch[x][0]) {
            siz[x]+=siz[ch[x][0]];
            maintain(fir,sec,f[ch[x][0]]);
            maintain(fir,sec,s[ch[x][0]]);
        }
        if(ch[x][1]) {
            siz[x]+=siz[ch[x][1]];
            maintain(fir,sec,f[ch[x][1]]);
            maintain(fir,sec,s[ch[x][1]]);
        }
        f[x]=fir,s[x]=sec,cntf[x]=cnts[x]=0;
        if(val[x]==fir) cntf[x]++;
        if(val[x]==sec) cnts[x]++;

        if(ch[x][0]) {
            if(f[ch[x][0]]==fir) cntf[x]+=cntf[ch[x][0]];
            if(f[ch[x][0]]==sec&&sec!=-inf) cnts[x]+=cntf[ch[x][0]];
            if(s[ch[x][0]]==sec&&sec!=-inf) cnts[x]+=cnts[ch[x][0]];
        }
        if(ch[x][1]) {
            if(f[ch[x][1]]==fir) cntf[x]+=cntf[ch[x][1]];
            if(f[ch[x][1]]==sec&&sec!=-inf) cnts[x]+=cntf[ch[x][1]];
            if(s[ch[x][1]]==sec&&sec!=-inf) cnts[x]+=cnts[ch[x][1]];
        }
        
    }
    inline void pushall(int x) {
        if(not_root(x)) pushall(fa[x]);
        push_down(x);
    }
    inline void rotate(int x){
        int y=fa[x],z=fa[y],k=dir(x);
        if(ch[x][k^1]) fa[ch[x][k^1]]=y;ch[y][k]=ch[x][k^1];
        if(not_root(y)) ch[z][dir(y)]=x;fa[x]=z;
        ch[x][k^1]=y;fa[y]=x;
        push_up(y);
    }
    inline void splay(int x,int goal=0) {
        pushall(x);
        while(not_root(x)) {
            int y=fa[x],z=fa[y];
            if(not_root(y)) {
                if(dir(x)==dir(y)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        push_up(x);
    }
    inline void access(int x) {    //从原树的根向x拉一条实链
        for(int y=0;x;y=x,x=fa[x]) {
            splay(x);ch[x][1]=y;push_up(x);
        }
    }
    inline void make_root(int x) {  //使x成为splay的根
        access(x);splay(x);mark_rev(x);
    }
    inline int find_root(int x) {   //找到x在原树中的根
        access(x);splay(x);
        while(ch[x][0]) push_down(x),x=ch[x][0];
        splay(x);
        return x;
    }
    inline void split(int x,int y) {   //拉出一条x->y的实链,y为splay根
        make_root(x);access(y);splay(y);
    }
    inline bool link(int x,int y) {    //连接x与y,若已经在同一颗原树中，返回0
        make_root(x);
        if(find_root(y)==x) return 0;
        fa[x]=y;return 1;
    } 
    inline bool cut(int x,int y) {
        make_root(x);
        if(find_root(y)!=x||fa[y]!=x||ch[y][0]) return 0;
        fa[y]=ch[x][1]=0;
        push_up(x);
        return 1;
    }

    inline void update(int u,int v,int w) { //区间改值
        split(u,v);mark_upd(v,w);
    }
    inline void add(int u,int v,int w) { //区间加值
        split(u,v);mark_add(v,w);
    }
    inline void solve(int u,int v) {
        split(u,v);
        if(s[v]==-inf) {printf("ALL SAME\n");return;}
        printf("%d %d\n",s[v],cnts[v]);
    }
};
using namespace LCT;

int n,m,a,b,x,y,opt;
int main()
{
    int t;scanf("%d",&t);
    for(int cas=1;cas<=t;cas++) {
        scanf("%d %d",&n,&m);init(n);
        for(int i=1;i<=n;i++) scanf("%d",&val[i]);
        for(int i=1,u,v;i<n;i++) {
            scanf("%d %d",&u,&v);
            link(u,v);
        }
        printf("Case #%d:\n",cas);
        for(int i=1;i<=m;i++) {
            scanf("%d",&opt);
            if(opt==1) {
                scanf("%d %d %d %d",&x,&y,&a,&b);
                cut(x,y);link(a,b);
            }else if(opt==2) {
                scanf("%d %d %d",&a,&b,&x);
                update(a,b,x);
            }else if(opt==3) {
                scanf("%d %d %d",&a,&b,&x);
                add(a,b,x);
            }else {
                scanf("%d %d",&a,&b);
                solve(a,b);
            }
        }
    }
}