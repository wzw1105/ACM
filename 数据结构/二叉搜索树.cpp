#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;

struct binary_tree{
	int tot,roo;
	binary_tree(){
		tot=0;
	}
	struct data{
		int ls,rs,val;
	}node[maxn*20];

	void insert(int k,int id){
		if(node[id].val==k) return;
		if(!tot) {
			node[++tot].val=k;
			roo=tot;
			return;
		}

		if(k<=node[id].val){
			if(!node[id].ls) {
				node[id].ls=++tot;
				node[node[id].ls].val=k;
				return;
			}else insert(k,node[id].ls);
		}else{
			if(!node[id].rs){
				node[id].rs=++tot;
				node[node[id].rs].val=k;
				return;
			}else insert(k,node[id].rs);
		}
	}

	void mid_visit(int id,int type){ //type:0：前序遍历，1:中序遍历，2:后序遍历
		if(type==0) printf("%d ",node[id].val);
		if(node[id].ls) mid_visit(node[id].ls,type);
		if(type==1) printf("%d ",node[id].val);
		if(node[id].rs) mid_visit(node[id].rs,type);
		if(type==2) printf("%d ",node[id].val);
	}
}tree;

int n,a;

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a),tree.insert(a,tree.roo);
	tree.mid_visit(1,0);puts("");
	tree.mid_visit(1,1);puts("");
	tree.mid_visit(1,2);puts("");
}