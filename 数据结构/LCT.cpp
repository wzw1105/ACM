/*
BZOJ3669:就是给你一张无向图，每一条边都有两个属性ai和bi，你拥有两个属性值A和B，能通过一条边当且仅当A>ai且B>bi，通过后A和B不变，求满足能从1走到n的最小A+B
按ai升序排序，然后LCT维护bi的最小生成树，因为求路径最大边权最小就是kruskal跑最小生成树，所以维护这个最小生成树就行了

1. 实链的根结点不记录father,但是他的father记录他为儿子
2. 虚链的根结点记录father,但是他的father不记录他为儿子
3. LCT维护树链上的值的时候得先把节点value加上去，然后才能link，因为如果link之后改value,有可能在link的时候一些节点信息没有更新为正确值
4. find_root很慢，可以用并查集辅助查询
5. val用于记录每个节点的值
6. LCT的主要作用就是维护删边加边的一些操作，还常用语维护最小生成树，比如下面这个代码
7. 自己实现一些LCT的函数时，要注意是否需要下放标记，上传标记，稍不注意可能就会wa
8. 对于LCT实现的一些简单路径所有节点修改操作，可以将标记放在区间翻转操作一起，同步下放标记，所以LCT很好维护 ，只用修改push_down函数就行了
9. 注意split以及link函数里包含make_root函数，所以会改变原树的根
10. 注意每个节点都可能有翻转标记，自己实现函数的时候需要考虑到下放标记
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;
#define inf 0x3f3f3f3f

namespace LCT{
    int ch[maxn][2],fa[maxn],mark[maxn];
    int val[maxn],ans[maxn],sum[maxn];
    inline bool not_root(int x) {return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
    inline int dir(int x) {return ch[fa[x]][1]==x;}
    inline void add_mark(int x) {swap(ch[x][0],ch[x][1]);mark[x]^=1;}        //将x这颗子树翻转
    inline void push_down(int x) {
        if(mark[x]) {
            if(ch[x][0]) add_mark(ch[x][0]);
            if(ch[x][1]) add_mark(ch[x][1]); 
            mark[x]=0;
        }
    }

    /*inline void push_up(int x) {
        ans[x]=val[x];sum[x]=val[x];
        if(ch[x][0]) ans[x]=max(ans[x],ans[ch[x][0]]),sum[x]+=sum[ch[x][0]];
        if(ch[x][1]) ans[x]=max(ans[x],ans[ch[x][1]]),sum[x]+=sum[ch[x][1]];
        
    }*/
    //维护最小生成树所用的push_up,由于环的时候需要查询最大值的位置然后去cut,所以需要记录节点而不是值
    inline void push_up(int x) {
        ans[x]=x;
        if(val[ans[ch[x][0]]]>val[ans[x]]) ans[x]=ans[ch[x][0]];
        if(val[ans[ch[x][1]]]>val[ans[x]]) ans[x]=ans[ch[x][1]];    
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
    inline void make_root(int x) {  //使x成为原树的根
        access(x);splay(x);add_mark(x);
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
    inline long long query_max(int l,int r) {
        split(l,r);
        return ans[r];
    }
    inline long long query_sum(int l,int r) {
        split(l,r);
        return sum[r];
    }
};
using namespace LCT;

struct edge{
    int u,v,a,b;
    friend bool operator<(const edge &c,const edge &d) {
        return c.a<d.a;
    }
}o[maxn];

int n,m;
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d %d %d %d",&o[i].u,&o[i].v,&o[i].a,&o[i].b);
    sort(o+1,o+m+1);
    int ans=inf;
    for(int i=1;i<=m;i++) {                         //相当于枚举属性A的最大值，然后找最小的B
        if(find_root(o[i].u)==find_root(o[i].v)){   //同一个集合
            int u=query_max(o[i].u,o[i].v);         //找到最大的点
            if(o[i].b<val[u]) {                     //已经存在的路径上的最大值大于当前边
                cut(o[u-n].u,u);
                cut(o[u-n].v,u);
            }else {
                if(find_root(1)==find_root(n)) ans=min(ans,o[i].a+val[query_max(1,n)]);
                continue;
            }
        }
        val[i+n]=o[i].b;
        link(o[i].u,i+n);link(o[i].v,i+n);    //新建虚拟节点i+n用来存储(o[i].u,o[i].v)的边权
        if(find_root(1)==find_root(n)) ans=min(ans,o[i].a+val[query_max(1,n)]);
    } 
    if(ans==inf) printf("%d\n",-1);
    else printf("%d\n",ans);
}