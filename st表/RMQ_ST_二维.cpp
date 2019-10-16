#include<cstdio>
#include<algorithm>

using namespace std;

const int maxn=251;

int m,n,a[maxn][maxn],dp[2][maxn][maxn][9][9];
struct st{
	int dp[2][maxn][maxn][9][9];
	void init()
	{
		for(int k=0;k<=1;k++){
			for(int i=1;i<=m;i++){
				for(int j=1;j<=n;j++){
					dp[k][i][j][0][0]=a[i][j];
				}
			}
		}
		for(int k=0;(1<<k)<=m;k++){
			for(int l=0;(1<<l)<=n;l++){
				for(int i=1;i+(1<<k)-1<=m;i++){
					for(int j=1;j+(1<<l)-1<=n;j++){
						int x=k?k-1:0,y=l?l-1:0;
						int lx=k?(1<<(k-1)):0,ly=l?(1<<(l-1)):0;
						dp[0][i][j][k][l]=min(dp[0][i][j][x][y],min(dp[0][i+lx][j][x][y],min(dp[0][i][j+ly][x][y],dp[0][i+lx][j+ly][x][y])));
						dp[1][i][j][k][l]=max(dp[1][i][j][x][y],max(dp[1][i+lx][j][x][y],max(dp[1][i][j+ly][x][y],dp[1][i+lx][j+ly][x][y])));
					}
				}
			}
		}
	}

	pair<int,int> query(int c,int d,int e,int f)  
	{
		int k1=0,k2=0;
		while(c+(1<<(k1+1))<=e) k1++;
		while(d+(1<<(k2+1))<=f) k2++;
		int nxtx=e-(1<<k1)+1,nxty=f-(1<<k2)+1;
		int maxx=max(dp[1][c][d][k1][k2],max(dp[1][nxtx][d][k1][k2],max(dp[1][c][nxty][k1][k2],dp[1][nxtx][nxty][k1][k2])));
		int minn=min(dp[0][c][d][k1][k2],min(dp[0][nxtx][d][k1][k2],min(dp[0][c][nxty][k1][k2],dp[0][nxtx][nxty][k1][k2])));
		return make_pair(minn,maxx);
	}
}arr;

int b,k,x,y;

int main()
{
	scanf("%d %d %d",&n,&b,&k);m=n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	arr.init();
	for(int i=1;i<=k;i++){
		scanf("%d %d",&x,&y);
		pair<int,int> ans=arr.query(x,y,x+b-1,y+b-1);
		printf("%d\n",ans.second-ans.first);
	}
}

/*
5 3 100
5 1 2 6 3
1 3 5 2 7
7 2 4 6 1
9 9 8 6 5
0 6 9 3 9
1 2
3 3
1 3
*/


