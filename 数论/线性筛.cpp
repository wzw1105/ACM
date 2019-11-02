#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5,maxl=103;
int n,prim[maxn],check[maxn],len=0;

void get_prim() {
	for(int i=2;i<=maxl;i++){
		if(!check[i]) prim[++len]=i;
		for(int j=1;j<=len&&i*prim[j]<=maxl;j++){
			check[i*prim[j]]=1;
			if(i%prim[j]==0) break;
		}
	}
}

int main() {
	get_prim();
	for(int i=1;i<=len;i++) printf("%d ",prim[i]); 
}
