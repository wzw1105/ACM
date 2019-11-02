#include<bits/stdc++.h>

using namespace std;
const int maxn=10005;      // max node
const int maxm=10005;      // max operate/query
const int max_col=1000005; // max color
/*
color临时存每个位置的颜色
numq:number of query   numo:number of operate
num:每个颜色的数量
res:当前区间答案
id:id-th query 
change:number of change before him    
*/
int ans[maxm],a[maxn]; //a:initial cilor
int block_size,block[maxn],numq,numo,color[maxn],num[max_col],res;       
struct query{                                                                  
    int id,l,r,change;   //
    query(int a=0,int b=0,int c=0,int d=0) {                                   
        id=a;l=b;r=c;change=d;
    }
    friend bool operator<(const query&a,const query&b){
        if(block[a.l]^block[b.l]) return a.l<b.l;
        if(block[a.r]^block[b.r]) return a.r<b.r;
        return a.change<b.change;
    }
}q[maxm];

struct operate{
    int pos,pre,nxt;  //pos记录修改的位置,pre为修改之前的数,nxt为修改后的数
    operate(int a=0,int b=0,int c=0) {
        pos=a;pre=b;nxt=c;
    }
}o[maxm];

void init(int n) {
    numq=numo=0;
    block_size=(int)pow(n,2.0/3);
    for(int i=1;i<=n;i++) block[i]=i/block_size;
}

void add_change(int id,int l,int r) {
    if(o[id].pos>=l&&o[id].pos<=r) {
        if(--num[a[o[id].pos]]==0) res--;
        if(++num[o[id].nxt]==1) res++;
    }
    a[o[id].pos]=o[id].nxt;
}

void del_change(int id,int l,int r) {
    if(o[id].pos>=l&&o[id].pos<=r) {
        if(--num[a[o[id].pos]]==0) res--;
        if(++num[o[id].pre]==1) res++;
    }
    a[o[id].pos]=o[id].pre;
}

void add(int id) {if(++num[a[id]]==1) res++;}
void del(int id) {if(--num[a[id]]==0) res--;}
void mo_dui() {
    int l=1,r=0,k=0;  //k为前缀修改数量
    for(int i=1;i<=numq;i++) {
        while(k<q[i].change) add_change(++k,l,r);
        while(k>q[i].change) del_change(k--,l,r);
        while(l<q[i].l) del(l++);
        while(l>q[i].l) add(--l);
        while(r<q[i].r) add(++r);
        while(r>q[i].r) del(r--);
        ans[q[i].id]=res;
    }
}

int n,m,x,y;
char opt[10];
int main() {
    scanf("%d %d",&n,&m);init(n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),color[i]=a[i];
    for(int i=1;i<=m;i++) {
        scanf("%s %d %d",opt+1,&x,&y);
        if(opt[1]=='Q') q[numq+1]=query(numq+1,x,y,numo),numq++;
        else o[++numo]=operate(x,color[x],y),color[x]=y;
    }
    sort(q+1,q+numq+1);
    mo_dui();
    for(int i=1;i<=numq;i++) printf("%d\n",ans[i]);
}