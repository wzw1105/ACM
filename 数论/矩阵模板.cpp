#include<cstring>
#include<cstdio>

using namespace std;
typedef long long ll;
const int maxn=300;
int mod=1e9+7;
int n;

struct matrix{
	ll mat[maxn][maxn];int siz;
	matrix(int a=maxn){
		siz=a-1;
		memset(mat,0,sizeof(mat));
	}
	matrix operator*(const matrix &b){
		matrix res;
		for(int i=1;i<=siz;i++){
			for(int k=1;k<=siz;k++){
				if(mat[i][k]){
					for(int j=1;j<=siz;j++){
						if(b.mat[k][j]){
							res.mat[i][j]=(res.mat[i][j]+(mat[i][k]*b.mat[k][j]));
							if(res.mat[i][j]>=mod) res.mat[i][j]%=mod;
						}
					}
				}
			}
		}
		return res;
	}
	matrix pow(long long k){
		matrix res,tmp=*this;
		for(int i=1;i<=siz;i++) res.mat[i][i]=1;
		while(k){
			if(k&1) res=res*tmp;
			tmp=tmp*tmp;
			k>>=1;
		}
		return res;
	}
	void print(){
		for(int i=1;i<=siz;i++){
			for(int j=1;j<=siz;j++){
				printf("%lld%c",mat[i][j],j==siz?'\n':' ');
			}
		}
	}
}a,b,res;

int main()
{
	
}