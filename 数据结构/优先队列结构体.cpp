#include<bits/stdc++.h>

using namespace std;

template<typename E>
struct node{
	E l,r;
	node(E a=0,E b=0){
		l=a,r=b;
	}
	friend bool operator<(const node& a,const node& b){
		return a.l>b.l;
	}
};

node<int> a[1000]; 

priority_queue<node<int> > que;

int main()
{
	for(int i=1;i<=10;i++){
		a[i]=node<int>(i,10-i+1);
		que.push(a[i]);
	}
	
	while(!que.empty()){
		node<int> tmp=que.top();
		printf("%d %d\n",tmp.l,tmp.r);
		que.pop();
	}
}
