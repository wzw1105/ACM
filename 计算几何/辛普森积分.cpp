#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,l,r;
double f(double x) {return (c*x+d)/(a*x+b);}
double simpson(double l,double r) {return (r-l)*(f(l)+f(r)+4*f((l+r)/2))/6;}
double area(double l,double r,double eps,double last_area) {
	double mid=(l+r)/2;
	double l_area=simpson(l,mid),r_area=simpson(mid,r);
	if(fabs(last_area-l_area-r_area)<15*eps) return l_area+r_area+(l_area+r_area-last_area)/15;
	return area(l,mid,eps,l_area)+area(mid,r,eps,r_area);
}
int main() {
	scanf("%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&l,&r);
	printf("%.6lf\n",area(l,r,1e-7,simpson(l,r)));
}