#include<cstdio>
#include<iostream>
#include<cmath>

using namespace std;
const int maxn=1e6+10;

int n,k,a[maxn],que[maxn],tot,head,tail,minn[maxn],maxx[maxn]; 

void solve_min() //解决所有长度为k的所有连续区间最小值问题
{
	head=1;tail=0;
	for(int i=1;i<k;i++) {
		while(head<=tail&&a[i]<a[que[tail]]) tail--;
		que[++tail]=i;
	}
	for(int i=k;i<=n;i++) {
		while(head<=tail&&que[head]<=i-k) head++;
		while(head<=tail&&a[i]<a[que[tail]]) tail--;
		que[++tail]=i;

		minn[i-k+1]=a[que[head]];
	}
}

void solve_max() //解决所有长度为k的所有连续区间最大值问题
{
	head=1;tail=0;
	for(int i=1;i<k;i++) {
		while(head<=tail&&a[i]>a[que[tail]]) tail--;
		que[++tail]=i;
	}
	for(int i=k;i<=n;i++) {
		while(head<=tail&&que[head]<=i-k) head++;
		while(head<=tail&&a[i]>a[que[tail]]) tail--;
		que[++tail]=i;

		maxx[i-k+1]=a[que[head]];
	}
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	solve_min();solve_max();
	for(int i=1;i+k-1<=n;i++) printf("%d%c",i+k-1==n?'\n':' ');
	for(int i=1;i+k-1<=n;i++) printf("%d%c",i+k-1==n?'\n':' ');
}