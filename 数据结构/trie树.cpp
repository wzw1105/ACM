#include<bits/stdc++.h>

using namespace std;
#define maxnode 100005
#define sigma_size 26

struct trie{
	int ch[maxnode][sigma_size],val[maxnode],sz;
	trie(){
		memset(ch[0],0,sizeof(ch[0]));
		memset(val,0,sizeof(val));
		sz=1;
	}
	int idx(char c) {return c-'A';} 
	void insert(char *s,int v){
		int u=0,n=strlen(s+1);
		for(int i=1;i<=n;i++){
			int c=idx(s[i]);
			if(!ch[u][c]){
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
				ch[u][c]=sz++;
			}
			u=ch[u][c];
		}
		val[u]=v;
	}
};
