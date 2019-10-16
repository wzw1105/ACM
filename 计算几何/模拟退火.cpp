#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+10;
double x[maxn],y[maxn],w[maxn];
int n;

namespace simulated_annealing {
	double ansx,ansy; //全局最优解的坐标
	double ans;       // 全局最优解,温度
	const double delta=0.996; //降温系数,系数越大,运行时间越长,准确度越高,可调节,(0.999)
	inline double dis(double a,double b,double c,double d) {
		return sqrt((a-c)*(a-c)+(b-d)*(b-d));
	}
	inline double calc_energy(double a,double b) {  //计算决策点在(a,b)处时的能量
		double res=0;
		for(int i=1;i<=n;i++) res+=dis(a,b,x[i],y[i])*w[i];
		return res;
	}	
	inline void init() {     //初始化
		ansx=ansy=0;
		for(int i=1;i<=n;i++) ansx+=x[i],ansy+=y[i];
		ansx/=n,ansy/=n;
		ans=calc_energy(ansx,ansy);
	}
	inline void simulate() {
		double nowx=ansx,nowy=ansy; //当前搜索到的点
		double t=3000;      //初识温度可调节
		while(t>1e-14) {  //精度可调节
			double nxtx=nowx+(rand()*2-RAND_MAX)*t;
			double nxty=nowy+(rand()*2-RAND_MAX)*t;
			double nxt_energy=calc_energy(nxtx,nxty);
			double delta_energy=nxt_energy-ans;        //能量差
			if(delta_energy<0) nowx=ansx=nxtx,nowy=ansy=nxty,ans=nxt_energy;      //能量降低一定接受新点
			else if(exp(-delta_energy/t)*RAND_MAX>rand()) nowx=nxtx,nowy=nxty;   //以一定的概率接受这个点
			t*=delta;       //降温
		}
	}
	inline void solve() {
		init();
		simulate();
		simulate();
		simulate();
		simulate();
		simulate();
		simulate();
		simulate();
		simulate();
		simulate();
	}
}
using namespace simulated_annealing;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lf %lf %lf",&x[i],&y[i],&w[i]);
	solve();
	printf("%.3lf %.3lf\n",ansx,ansy);
}