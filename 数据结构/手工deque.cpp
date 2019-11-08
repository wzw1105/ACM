#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct dequeue_{
	int a[maxn],L,R,siz=0;
	bool empty() {return siz==0;}
	dequeue_(int l=1,int r=0,int siz_=0) {L=l,R=r,siz=siz_;} 
	void clear() {
		L=1,R=0,siz=0;
	}
	bool push_front(int val) {
		if(siz==maxn-1) return false;
		if(L==1) L=maxn-1,a[L]=val,siz++;
		else L--,a[L]=val,siz++;
		return true;
	}
	bool push_back(int val) {
		if(siz==maxn-1) return false;
		if(R==maxn-1) R=1,a[R]=val,siz++;
		else R++,a[R]=val,siz++;
		return true;
	} 
	int pop_front() {
		if(siz==0) return 0;
		int ans=0;
		if(L==maxn-1) ans=a[L],L=1,siz--;
		else ans=a[L],L++,siz--;
		return ans;
	}
	int pop_back() {
		if(siz==0) return 0;
		int ans=0;
		if(R==1) ans=a[R],R=maxn-1,siz--;
		else ans=a[R],R--,siz--;
		return ans;
	}
	int front() {return a[L];}
	int back() {return a[R];}
};