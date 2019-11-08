/*
POJ1860:有n种货币，给出一些两种货币之间的汇率以及你开始有的货币种类以及钱的数量，
问你是否可以让这些钱经过一些转换之后使得回到开始时的货币种类并且使得手中的钱币开始多
可以考虑bellman_ford判断是否有一个正权的环，如果有，那么就可以变大
*/
#include<cstdio>
using namespace std;
const int maxn=205;
const int maxm=205;

int n,m,s,tot;
double dis[maxn],money;
struct edge{
	int u,v;
	double r,c;
	edge(int a=0,int b=0,double r_=0,double c_=0) {u=a,v=b,r=r_,c=c_;}
}e[maxm];

bool bellman_ford(int s) {  
	for(int i=1;i<=n;i++) dis[i]=0;
	dis[s]=money;
	for(int i=1;i<=n;i++) {
		bool update=false;
		for(int j=1;j<=tot;j++) {
			if(dis[e[j].v]<(dis[e[j].u]-e[j].c)*e[j].r) {  //判断负环之用<改成>
				update=true;
				dis[e[j].v]=(dis[e[j].u]-e[j].c)*e[j].r;
				if(i==n) return true;
			}
		}
		if(!update) break;
	}
	return false;
}

int main() {
	scanf("%d %d %d %lf",&n,&m,&s,&money);
	for(int i=1;i<=m;i++) {
		int u,v;
		double rab,cab,rba,cba;
		scanf("%d %d %lf %lf %lf %lf",&u,&v,&rab,&cab,&rba,&cba);
		e[++tot]=edge(u,v,rab,cab);
		e[++tot]=edge(v,u,rba,cba);
	}
	printf(bellman_ford(s)?"YES\n":"NO\n");
}