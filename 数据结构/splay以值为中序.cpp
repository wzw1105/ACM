/*
洛谷P3369:
1.插入x数
2.删除x数(若有多个相同的数，因只删除一个)
3.查询x数的排名(排名定义为比当前数小的数的个数+1。若有多个相同的数，因输出最小的排名)
4.查询排名为x的数
5.求x的前驱(前驱定义为小于x，且最大的数)
6.求x的后继(后继定义为大于x，且最小的数)
*/
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
const int maxn=2e5+10;

struct splay_tree{
    int tot,root,ch[maxn][2],val[maxn],cnt[maxn],fa[maxn],siz[maxn],mark[maxn][3];//mark第二维表示存不同的标记
    splay_tree(){       
        tot=0;
        root=0;
        insert(-inf);insert(inf);  //插入两个边界的数方便区间翻转和元素删除操作
    }
    int dir(int x) {return ch[fa[x]][1]==x;}
    void pushup(int x){
        siz[x]=cnt[x];
        if(ch[x][0]) siz[x]+=siz[ch[x][0]];
        if(ch[x][1]) siz[x]+=siz[ch[x][1]];
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],k=dir(x);
        ch[y][k]=ch[x][k^1];fa[ch[x][k^1]]=y;
        ch[z][dir(y)]=x;fa[x]=z;
        ch[x][k^1]=y;fa[y]=x;
        pushup(y);pushup(x);
    }
    void splay(int x,int goal=0){
        while(fa[x]!=goal){
            int y=fa[x],z=fa[y];
            if(z!=goal) {
                if(dir(x)==dir(y)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        if(!goal) root=x;
    }
    void insert(int x){  //x 为插入的位置，x为插入的值
        int cur=root,pre=0;
        while(cur&&val[cur]!=x) pre=cur,cur=ch[cur][x>val[cur]];
        if(cur) cnt[cur]++;  //存在该值的节点
        else{
            cur=++tot;
            if(pre) ch[pre][x>val[pre]]=cur;fa[cur]=pre;
            ch[cur][0]=ch[cur][1]=0;
            val[cur]=x;cnt[cur]=siz[cur]=1;
        }
        splay(cur); //splay到根节点，保持树平衡
    }
    int kth(int x){  //返回第x大,返回的是下标
        int cur=root;
        while(true){
            if(ch[cur][0]&&x<=siz[ch[cur][0]]){
                cur=ch[cur][0];
            }else if(x>siz[ch[cur][0]]+cnt[cur]){
                x-=(siz[ch[cur][0]]+cnt[cur]);
                cur=ch[cur][1];
            }else return cur;  
        }
    }
    int rank(int x){
        int ans=0,now=root;
        while(true){
            if(val[now]==x) {
                ans+=(ch[now][0]?siz[ch[now][0]]:0);
                splay(now);  //不做一次splay会被卡
                return ans;
            }
            if(now==0) return ans;
            if(x<val[now]) now=ch[now][0];
            else{
                ans+=(ch[now][0]?siz[ch[now][0]]:0)+cnt[now];
                now=ch[now][1];
            }
        }
        if(now) splay(now);
        return ans;
    }
    int pre(int x){ //前驱，即小于x的最大的数，返回下标
        int now=root,res=-inf-1,node;
        while(now){
            if(val[now]<x&&val[now]>res) node=now,res=val[now];
            if(x>val[now]) now=ch[now][1];
            else now=ch[now][0];
        }
        return node;
    }
    int next(int x){ //后继，即大于x的最小的数
        int now=root,res=inf+1,node;
        while(now){
            if(val[now]>x&&val[now]<res) node=now,res=val[now];
            if(x<val[now]) now=ch[now][0];
            else now=ch[now][1];
        }
        return node;
    }
    void erase(int x){  //erase的是值，即val
        int cur=pre(x),rson=next(x);
        splay(cur);splay(rson,root);
        if(cnt[ch[rson][0]]>1) {
            cnt[ch[rson][0]]--;
            splay(ch[rson][0]);
        }
        else ch[rson][0]=0;
        pushup(rson);pushup(root);
    }
    void mid_visit(int cur){ //中序遍历
        if(ch[cur][0]) mid_visit(ch[cur][0]);
        if(val[cur]!=-inf&&val[cur]!=inf)printf("%d ",val[cur]);
        if(ch[cur][1]) mid_visit(ch[cur][1]);
    }
}tree;

int n,a,m,l,r,opt;
int main() {
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d",&opt,&a);
        if(opt==1) tree.insert(a);
        else if(opt==2) tree.erase(a);
        else if(opt==3) printf("%d\n",tree.rank(a));
        else if(opt==4) printf("%d\n",tree.val[tree.kth(a+1)]);
        else if(opt==5) printf("%d\n",tree.val[tree.pre(a)]);
        else printf("%d\n",tree.val[tree.next(a)]);
    }
}