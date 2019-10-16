#include<bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;
#define eps 1e-9
#define inf 2e18
#define L 0
#define R 1e9

struct line{
	long long k,b;
	int l,r,flag,ls,rs;  //l,r表示线段的左端点和右端点，而线段树的左端点和右端点是不显示存储的,ls左儿子，rs右儿子
	line(long long a=0,long long c=0,int d=0,int e=0,int f=0,int g=0,int h=0){
		k=a;b=c;l=d;r=e;flag=f;ls=g;rs=h;
	}
}seg[maxn*30];

struct segment_tree{
	int tot;
	segment_tree() {tot=1;}
	inline long long calc(line l1,int pos) {return l1.k*pos+l1.b;}  //kx+b
	inline long long cross(line l1,line l2) {return (long long)((l1.b-l2.b)/(l2.k-l1.k));}  //l1 l2交点

	void insert(int le,int ri,int id,line ins){  //le,ri为需要维护的区间,id为线段树区间编号,ins为需要插入的线段
		if(ins.l>ins.r) return;
		if(ins.l<=le&&ins.r>=ri){
			if(!seg[id].flag) {
				swap(seg[id],ins);seg[id].ls=ins.ls;seg[id].rs=ins.rs;
			}
			else if((calc(ins,le)-calc(seg[id],le))>eps&&(calc(ins,ri)-calc(seg[id],ri))>eps) {
				swap(seg[id],ins);seg[id].ls=ins.ls;seg[id].rs=ins.rs;
			}
			else if((calc(ins,le)-calc(seg[id],le))>eps||(calc(ins,ri)-calc(seg[id],ri))>eps){
				int mid=(le+ri)>>1;
				if(calc(ins,mid)-calc(seg[id],mid)>eps) {
					swap(seg[id],ins);seg[id].ls=ins.ls;seg[id].rs=ins.rs;
				}
				if(cross(seg[id],ins)-mid<-eps) {
					if(!seg[id].ls) seg[id].ls=++tot;
					insert(le,mid,seg[id].ls,ins);
				}
				else if(cross(seg[id],ins)-mid>eps) {
					if(!seg[id].rs) seg[id].rs=++tot;
					insert(mid+1,ri,seg[id].rs,ins);
				}
				else{
					if(calc(seg[id],le)<calc(ins,le)) {
						if(!seg[id].ls) seg[id].ls=++tot;
						insert(le,mid,seg[id].ls,ins);
					}
					else {
						if(!seg[id].rs) seg[id].rs=++tot;
						insert(mid+1,ri,seg[id].rs,ins); 
					}
				}
			}
		}else{
			int mid=(le+ri)>>1;
			if(ins.l<=mid) {
				if(!seg[id].ls) seg[id].ls=++tot;
				insert(le,mid,seg[id].ls,ins);
			}
			if(ins.r>mid) {
				if(!seg[id].rs) seg[id].rs=++tot;
				insert(mid+1,ri,seg[id].rs,ins);
			}
		}
	}

	long long query(int le,int ri,int id,int pos){ //le,ri表示当前询问的区间
		if(le==ri) return calc(seg[id],pos);
		int mid=(le+ri)>>1;long long res=calc(seg[id],pos);
		if(pos<=mid&&seg[id].ls)  res=max(res,query(le,mid,seg[id].ls,pos));
		else if(pos>mid&&seg[id].rs) res=max(res,query(mid+1,ri,seg[id].rs,pos));
		return res;
	}
}tree;

char opt[100];
vector<pair<int,long long> > pos[maxn];
int a[maxn],n,m,x,t,que[3*maxn],cnt=0;long long k;


int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		scanf("%d %s",&t,opt+1);
		if(opt[1]=='q') que[++cnt]=t;
		else{
			scanf("%d %lld",&x,&k);
			pos[x].push_back(make_pair(t,k));
		}
	}
	for(int i=1;i<=n;i++) pos[i].insert(pos[i].begin(),make_pair(0,0)),pos[i].insert(pos[i].end(),make_pair(1e9+1,0));
	for(int i=1;i<=n;i++){
		long long last=a[i];
		for(int j=0;j<pos[i].size()-1;j++){
			long long b=last-pos[i][j].first*pos[i][j].second,k=pos[i][j].second;
			tree.insert(L,R,1,line(pos[i][j].second,b,pos[i][j].first,pos[i][j+1].first-1,1));
			tree.insert(L,R,1,line(-pos[i][j].second,-b,pos[i][j].first,pos[i][j+1].first-1,1));
			last=pos[i][j].second*pos[i][j+1].first+b;
		}
	}
	for(int i=1;i<=cnt;i++) printf("%lld\n",tree.query(L,R,1,que[i]));
}

/*
1 3
0
0 command 1 -3
0 command 1 -6
8 query
*/