#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;

struct dical_tree{  //小根堆笛卡尔树,值val满足堆的性质,下标key满足二叉树的性质,注意每个节点的索引就是在原数组中的位置
    int tot,sta[maxn],root; //sta维护单调值对应的在tree中的下标,tot表示栈顶的下标,root为树根
    struct node{             //sta维护的是最靠右的一条链
        int val;
        int fa,ls,rs;
        node(int v=0,int f=0,int l=0,int r=0) {
            val=v;fa=f;ls=l;rs=r;
        }
    }tree[maxn];

    void build(int a[],int n) {
        tot=root=1;
        sta[1]=1;tree[1]=node(a[1],0,0,0);
        for(int i=2;i<=n;i++) {
            while(tot&&a[i]<tree[sta[tot]].val)  tot--;//大根堆改为>
            if(tot) {  //此时需要将新建节点替换tot的右儿子，并把之前的右儿子接到新建节点的左儿子身上，以保证下标构成二叉树
                tree[i]=node(a[i],sta[tot],tree[sta[tot]].rs,0);
                tree[tree[sta[tot]].rs].fa=i;
                tree[sta[tot]].rs=i;                        
            }else {
                tree[i]=node(a[i],0,root,0);
                tree[root].fa=i;
                root=i;
            }
            sta[++tot]=i;
        }
    }
}dical;

int n,a[maxn];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	dical.build(a,n);
	dical.debug(n);
}