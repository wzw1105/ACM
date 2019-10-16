#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;

struct Hash{
    int base[3],mod[3];
    int tot,hash[3][maxn],pw[3][maxn]; //字符串长度,hash:记从1~i的hash值，pw:记录base^i
    Hash() {
        tot=0;
        for(int i=0;i<3;i++) pw[i][0]=1;
        base[0]=233;base[1]=19260817;base[2]=20030714;
        mod[0]=1e9+7;mod[1]=1e9+9;mod[2]=998244353;
    }

    void init() {
        tot=0;
    }
    void insert(int c) {
        tot++;
        for(int i=0;i<3;i++) hash[i][tot]=(1LL*hash[i][tot-1]*base[i]+c)%mod[i];
        for(int i=0;i<3;i++) pw[i][tot]=(1LL*pw[i][tot-1]*base[i])%mod[i];
    }
    //字符串[l,r]hash值,type为第几个hash
    int query(int l,int r,int type) { 
        return (hash[type][r]-(1LL*hash[type][l-1]*pw[type][r-l+1]%mod[type])+mod[type])%mod[type];
    }
    //判断字符串u的[lu,ru]内的字符串和字符串v的[lv,rv]内的字符串是否相同
    friend bool same(Hash &u,int lu,int ru,Hash &v,int lv,int rv) { 
        if(ru-lu!=rv-lv) return false;
        for(int i=0;i<3;i++) if(u.query(lu,ru,i)!=v.query(lv,rv,i)) return false;
        return true;
    }

}h1,h2;

char s[maxn];
char ans[maxn];
int len=0,n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",s+1);
        int m=strlen(s+1);
        if(i==1) {
            for(int j=1;j<=m;j++) {h1.insert(s[j]);ans[j]=s[j];}
            len=m;
        }else{
            int id=0;h2.init();
            for(int j=1;j<=m;j++) {
                h2.insert(s[j]);
                if(same(h1,max(1,h1.tot-j+1),h1.tot,h2,1,h2.tot)) id=j;
            }
            for(int j=id+1;j<=m;j++)  {
                h1.insert(s[j]);
                ans[++len]=s[j];
            }
        }
    }
    for(int i=1;i<=len;i++) printf("%c",ans[i]);
}