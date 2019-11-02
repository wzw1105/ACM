/*
POJ3580
ADD x y D:[x,y]都加上D
REVERSE x y:翻转区间[x,y]
REVOLVE x y T:旋转区间[x,y] T次. 比如2 4 2 on{1,2,3,4,5}=>{1,3,4,2,5}
INSERT x P:在位置x之后插入P
DELETE x:删除位置x的数
MIN x y:查询区间最小值[x,y]
*/
#include<cstdio>
#include<iostream>

using namespace std;
#define inf 0x3f3f3f3f
const int maxn=2e5+10;
/*
说明：
此splay树不能同时支持查询rank操作，如果需要同时支持区间翻转和查询rank，则需要写树套树
*/
struct splay_tree{
    int tot,root,ch[maxn][2],fa[maxn],siz[maxn],tmp;//mark第二维表示存不同的标记
    int minn[maxn],val[maxn],mark[maxn][3];
    splay_tree(){      
        tot=2;root=1;
        ch[1][1]=2;fa[2]=1;fa[1]=0;siz[1]=2;siz[2]=1;val[2]=minn[2]=inf;val[1]=minn[1]=-inf;  //插入两个边界的数方便区间翻转和元素删除操作
    }
    void init(){
        memset(ch,0,sizeof(ch));
        memset(siz,0,sizeof(siz));
        memset(fa,0,sizeof(fa));
        memset(mark,0,sizeof(mark));
        tot=2;root=1;
        ch[1][1]=2;fa[2]=1;fa[1]=0;siz[1]=2;siz[2]=1;val[2]=minn[2]=inf;val[1]=minn[1]=-inf;
    }
    int dir(int x) {return ch[fa[x]][1]==x;}
    void pushup(int x){
        siz[x]=1;minn[x]=val[x];
        if(ch[x][0]) minn[x]=min(minn[x],minn[ch[x][0]]),siz[x]+=siz[ch[x][0]];
        if(ch[x][1]) minn[x]=min(minn[x],minn[ch[x][1]]),siz[x]+=siz[ch[x][1]];
    }
    void down(int x){
        if(mark[x][0]){  //翻转标记
            swap(ch[x][0],ch[x][1]);
            mark[ch[x][0]][0]^=1;
            mark[ch[x][1]][0]^=1;
            mark[x][0]=0;
        }
        if(mark[x][1]){   //区间加
            mark[ch[x][0]][1]+=mark[x][1];
            mark[ch[x][1]][1]+=mark[x][1];
            val[ch[x][0]]+=mark[x][1];minn[ch[x][0]]+=mark[x][1];
            val[ch[x][1]]+=mark[x][1];minn[ch[x][1]]+=mark[x][1];
            mark[x][1]=0;
        }
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],k=dir(x);
        down(y);down(x);
        ch[y][k]=ch[x][k^1];fa[ch[x][k^1]]=y;
        ch[z][dir(y)]=x;fa[x]=z;
        ch[x][k^1]=y;fa[y]=x;
        pushup(y);pushup(x);
    }
    void splay(int x,int goal=0){  //将编号为x的节点splay到goal的儿子处
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
    int kth(int x){  //返回位置为x的数的编号,注意初始化时如果插入了两个数，则需要加一
        int cur=root;
        while(true){
            down(cur);
            if(ch[cur][0]&&x<=siz[ch[cur][0]]){
                cur=ch[cur][0];
            }else if(x>siz[ch[cur][0]]+1){
                x-=(siz[ch[cur][0]]+1);
                cur=ch[cur][1];
            }else return cur;  
        }
    }
    void insert(int pos,int value){  //x 为插入的位置，value为插入的值
        int cur=kth(pos),rson=kth(pos+1);
        splay(cur),splay(rson,root);
        ch[rson][0]=++tot;fa[tot]=rson;
        ch[tot][0]=ch[tot][1]=0;siz[tot]=1;
        val[tot]=minn[tot]=value;
        pushup(rson);pushup(root);
        splay(cur); //splay到根节点，保持树平衡
    }
    void erase(int pos){  //erase的是pos
        int cur=kth(pos),rson=kth(pos+2);
        splay(cur);splay(rson,root);
        ch[ch[rson][0]][0]=ch[ch[rson][0]][1]=0;
        val[ch[rson][0]]=minn[ch[rson][0]]=0;fa[ch[rson][0]]=0;siz[ch[rson][0]]=0;
        ch[rson][0]=0;
        pushup(rson);pushup(root);
    }
    void revolve(int l,int r,int t){ //将区间[l,r]旋转t次，如1 2 3 4 5 旋转2次后就变成4 5 1 2 3
        t=(t%(r-l+1)+(r-l+1))%(r-l+1);
        if(!t) return;
        int cur=kth(r-t+1),rson=kth(r+2);
        splay(cur);splay(rson,root);
        int memor=ch[rson][0];ch[rson][0]=0;
        cur=kth(l);rson=kth(l+1);
        splay(cur);splay(rson,root);
        ch[rson][0]=memor;fa[memor]=rson;
    }
    void modify(int l,int r,int add){ //区间加
        int cur=kth(l),rson=kth(r+2);
        splay(cur);splay(rson,root);
        minn[ch[rson][0]]+=add;
        val[ch[rson][0]]+=add;
        mark[ch[rson][0]][1]+=add;
        pushup(rson);pushup(root);
    }
    int query_min(int l,int r){
        int cur=kth(l),rson=kth(r+2);
        splay(cur);splay(rson,root);
        return minn[ch[rson][0]];
    }
    void reverse(int l,int r){  //区间翻转
        int cur=kth(l),rson=kth(r+2);
        splay(cur);splay(rson,root);
        mark[ch[rson][0]][0]^=1;
    }
    void cut(int l,int r,int pos){  //区间[l,r]剪切粘贴到剩下的数的第pos个后，pos<=(n-(r-l+1));
        int cur=kth(l),rson=kth(r+2);
        splay(cur);splay(rson,root);
        int tmp=ch[rson][0];ch[rson][0]=0;
        pushup(rson);pushup(root);
        cur=kth(pos+1),rson=kth(pos+2);
        splay(cur);splay(rson,root);
        ch[rson][0]=tmp;fa[tmp]=rson;
        pushup(rson);pushup(root);
    }
    void mid(int cur){ //中序遍历
        down(cur);
        if(ch[cur][0]) mid(ch[cur][0]);
        if(val[cur]!=inf&&val[cur]!=-inf) tmp++,printf("%d%c",val[cur],tmp==siz[root]-2?'\n':' ');
        if(ch[cur][1]) mid(ch[cur][1]);
    }
    void mid_visit(){
        tmp=0;
        mid(root);
    }
}tree;

int n,m,l,r,t,x,a,add,val;
char opt[50];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a);
        tree.insert(i,a);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%s",opt+1);
        if(opt[1]=='A'){
            scanf("%d %d %d",&l,&r,&add);
            tree.modify(l,r,add);
        }else if(opt[1]=='R'){
            if(opt[4]=='E'){
                scanf("%d %d",&l,&r);
                tree.reverse(l,r);
            }else{
                scanf("%d %d %d",&l,&r,&t);
                tree.revolve(l,r,t);
            }
        }else if(opt[1]=='I'){
            scanf("%d %d",&x,&val);
            tree.insert(x+1,val);  //在x后面插要加一
        }else if(opt[1]=='D'){
            scanf("%d",&x);
            tree.erase(x);
        }else{
            scanf("%d %d",&l,&r);
            printf("%d\n",tree.query_min(l,r));
        }
    }
}
