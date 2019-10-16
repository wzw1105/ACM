#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e5+10;
/*
sta:计算点双连通分量时,保留在当前BCC(Bioconnected Component)中的边
dfn:dfs序  low[i]:节点i在dfs树上指回的最小dfs序
dfs_clock:dfs计时器 tot:链式前向星总边数 cnt:当前栈(sta)中元素个数  bcc_cnt:记录bcc个数
is_cut[i]:节点i是否是割点
*/
namespace block{
	int n,m,head[maxn],dfn[maxn],low[maxn],bccno[maxn],dfs_clock,tot,cnt,bcc_cnt;
	bool is_cut[maxn];
	vector<int> bcc[maxn];
	struct ed {int u,v,w,next;}edge[2*maxm];
	ed sta[maxn];
	inline void init(int n) { //注意init操作包括清图
		tot=dfs_clock=cnt=bcc_cnt=0;
		for(int i=1;i<=n;i++) head[i]=dfn[i]=low[i]=bccno[i]=is_cut[i]=0;
	}
	inline void add_edge(int u,int v,int w) {
		edge[++tot]=ed{u,v,w,head[u]};
		head[u]=tot;
	} 
	//求点双连通分量
	inline int BCC(int u,int fa) {
		int lowu=dfn[u]=++dfs_clock,child=0;
		for(int i=head[u];i;i=edge[i].next){
			if(!dfn[edge[i].v]) {
				sta[++cnt]=edge[i],child++;
				int lowv=BCC(edge[i].v,u);
				lowu=min(lowu,lowv);
				if(lowv>=dfn[u]) {
					bcc[++bcc_cnt].clear();
					for(;;) {
						ed x=sta[cnt--];
						if(bccno[x.u]!=bcc_cnt) {bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;}
						if(bccno[x.v]!=bcc_cnt) {bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;}
						if(x.u==u && x.v==edge[i].v) break;
					}
				}
			}else if(dfn[edge[i].v]<dfn[u] && edge[i].v!=fa ){
				sta[++cnt]=edge[i];
				lowu=min(lowu,dfn[edge[i].v]);
			}
		}
		if(!fa && child==1) is_cut[u]=0;
		return low[u]=lowu;
	}
	inline void find_bcc() {
		for(int i=1;i<=n;i++) if(!dfn[i]) BCC(i,0);
	} 
}
using namespace block;
int main() {
	while(~scanf("%d %d",&n,&m)) {
		init(n);
		for(int i=1,u,v;i<=m;i++) {
			scanf("%d %d",&u,&v);
			add_edge(u,v,0);
			add_edge(v,u,0);
		} 
		find_bcc();
		printf("%d\n",bcc_cnt);
		for(int i=1;i<=bcc_cnt;i++) {
			for(int j=0;j<bcc[i].size();j++) {
				printf("%d%c",bcc[i][j],j==bcc[i].size()-1?'\n':' ');
			}
		}
	}
}