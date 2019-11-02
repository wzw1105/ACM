#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N=2000000,P=510510,Q=92160;
struct getnthprime
{   
    int prime[N+1],pi[N+1],e[P];
    void init(){
       for(int i=2;i<=N;i++) {
          if(!prime[i]) prime[++prime[0]]=i,pi[i]=pi[i-1]+1;
          else pi[i]=pi[i-1];
          for(int j=1;j<=prime[0]&&i<=N/prime[j];j++) {
              prime[i*prime[j]]=1;
              if(i%prime[j]==0) break;
          }
       }
       for(int i=0;i<P;i++) e[i]=i;
       for(int i=1;i<=7;i++) {
          for(int j=P-1;j>=0;j--)
            e[j]-=e[j/prime[i]];
       }
    }
    ll get_phi(ll m,int n) {
       if (n==7) return m/P*Q+e[m%P];
       if (m<prime[n]) return 1;
       if (m<=N&&m<=(ll)prime[n]*prime[n]*prime[n]) {
          ll ans=pi[m]-n+1;
          for(int i=n+1,l=pi[(int)sqrt(m+0.1)];i<=l;i++)
             ans+=pi[m/prime[i]]-i+1;
          return ans;
       }
       return get_phi(m,n-1)-get_phi(m/prime[n],n-1);
    }

    ll get_pi(ll m){
       if(m<=N) return pi[m];
       int n=pi[(int)cbrt(m-0.1)+1];
       ll ans=get_phi(m,n)+n-1;
       for(int i=n+1,l=pi[(int)sqrt(m+0.1)];i<=l;i++)
          ans-=get_pi(m/prime[i])-i+1;
       return ans;
   }

   bool f[1000010];
   ll get_pn(ll n) {
      if (n<=prime[0]) return prime[n];
      ll x=n*(log(n)+log(log(n))-1)+n*(log(log(n))-2)/log(n)-6*n/1000;
      ll y=n*(log(log(n)))*(log(log(n)))/log(n)/log(n);
      y=min(y,ll(3500000));
      ll l=x,r=x+y,flag = 0;
      for (int i=0;i<2;i++) {
         ll m=(l+r)>> 1;
         ll pm=get_pi(m);
         if(pm>=n) r=m,flag=0;
         else l=m+1,flag=pm;
      }
      ll count=flag?flag:get_pi(l-1);
      for(int i=1,li=pi[(int)sqrt(r+0.1)];i<=li;i++) {
         for(int j=((l-1)/prime[i]+1)*prime[i]-l;j<=r-l+1;
             j+=prime[i]){
             f[j]=true;
         } 
      }
      for(int i=0;i<=r-l+1;i++) {
         if(!f[i]){
             count++;
             if(count==n) return i+l;
         }
      }
      return -1;
   }
}NP;

int main() {
    NP.init();
    ll n; scanf("%lld",&n);
    cout<<NP.get_pn(n)<<endl;
    return 0;
}