#include<bits/stdc++.h>

using namespace std;
const int maxn=5e6;

long long n;  
int phi[maxn+10],prime[maxn+10],tot,ans;    
bool mark[maxn+10];  

void getphi()    
{    
   phi[1]=1;    
   for(int i=2;i<=maxn;i++)
   {    
       if(!mark[i]) {    
            prime[++tot]=i;
            phi[i]=i-1;
       }    
       for(int j=1;j<=tot;j++){    
          if(i*prime[j]>maxn)  break;    
          mark[i*prime[j]]=1;
          if(i%prime[j]==0){
             phi[i*prime[j]]=phi[i]*prime[j];break;    
          }    
          else  phi[i*prime[j]]=phi[i]*(prime[j]-1);
       }    
   }    
}

int main()
{
    getphi();
}
