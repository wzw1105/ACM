#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
//字符串从数组下标1开始
//nxt[i]表示子串T[1,i]的最长公共前缀后缀长度，前缀后缀可以重叠，但是长度不能为i
//s,t分别表示主串和模式串,n,m分别表示主串,模式串长度
namespace KMP{
    int nxt[maxn]; 
    //求出模式串的nxt数组
    void getnext(char t[],int m) {
        nxt[1]=0;
        for(int i=2;i<=m;i++) {
            int j=nxt[i-1];
            while(t[j+1]!=t[i] && j) j=nxt[j];
            if(t[j+1]==t[i]) nxt[i]=j+1;
            else nxt[i]=0;
        }
    }
    //求主串s与nxt数组对应的字符串的匹配信息
    void kmp(char s[],char t[],int n,int m) {
        getnext(t,m);
        int i=1,j=1; //i,j分别为s串和t串的指针
        while(i<=n) {
            if(s[i]==t[j]) {
                i++,j++;
                if(j==m+1) {
                    //此时找到一个与模式串一样的串,在主串的起始位置为i-m;
                    printf("%d\n",i-m);
                    j=nxt[j-1]+1;
                }
            }else {
                if(i==1) i++;  //第一个都不相同,指针i右移
                else j=nxt[j-1]+1;  //根据最长公共前缀后缀移动指针j
            }
        }
    }
}
using namespace KMP;

char s[1005],t[1005];
int n,m;
int main() {
    scanf("%s %s",s+1,t+1);
    n=strlen(s+1);
    m=strlen(t+1);
    kmp(s,t,n,m);
}