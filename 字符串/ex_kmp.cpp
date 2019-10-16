#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;

/*
1. nxt[i]表示子串t[i,m]与t[1,m]的最长公共前缀,extend[i]表示s[i,n]与t[1,m]的最长公共前缀
*/
namespace ex_kmp{
	int nxt[maxn],extend[maxn];
	//求出t串的nxt数组
	void getnext(char t[],int m) {
		int pos=2;            //pos用来记录i+pos[i]-1的最大值对应的i
		nxt[1]=m,nxt[2]=0;
		for(int i=1;i+1<=m && t[i]==t[i+1];i++,nxt[2]++); //计算nxt[2]
		for(int i=3;i<=m;i++) {
			if(i+nxt[i-pos+1]-1 < pos+nxt[pos]-1) nxt[i]=nxt[i-pos+1];
			else {
				int j=pos+nxt[pos]-i;  //j用来表示从相对t[0]的哪个位置开始匹配
				if(j<=0) j=1;        //此时从头开始匹配
				while(i+j-1<=m && t[j]==t[i+j-1]) j++;  //往后匹配
				nxt[i]=j-1,pos=i;      //更新最远点
			}
		}

	} 
	//求出extend数组
	void exkmp(char s[],char t[],int n,int m) {
		int pos=1;
		getnext(t,m);
		for(int i=1;i<=m && i<=n && s[i]==t[i];i++,extend[1]++);
		for(int i=2;i<=n;i++) {
			if(i+nxt[i-pos+1]-1 < pos+extend[pos]-1) extend[i]=nxt[i-pos+1];
			else {
				int j=pos+extend[pos]-i;
				if(j<=0) j=1;
				while(i+j-1<=n && j<=m && s[i+j-1]==t[j]) j++;
				extend[i]=j-1,pos=i;
			}

		}
	}
}
using namespace ex_kmp;
char s[maxn],t[maxn];
int n,m;

int main() {
	scanf("%s %s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	exkmp(s,t,n,m);
	for(int i=1;i<=n;i++) printf("%d%c",extend[i],i==n?'\n':' ');
}