#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;
#define eps 1e-9
#define inf 0x3f3f3f3f

struct line{
	double k,b;
	int l,r,flag;  //l,r表示线段的左端点和右端点，而线段树的左端点和右端点是不显示存储的
	line(double a=0,double c=0,int d=0,int e=0,int f=0){
		k=a;b=c;l=d;r=e;flag=f;
	}
}seg[maxn<<2];

struct segment_tree{
	inline double calc(line l1,int pos) {return l1.k*pos+l1.b;}  //kx+b
	inline int cross(line l1,line l2) {return floor((l1.b-l2.b)/(l2.k-l1.k));}  //l1 l2交点

	void build(int le,int ri,int id){   //这个操作好像没啥用233
		seg[id].l=1;seg[id].r=50000;seg[id].flag=0;
		if(le==ri) return;
		int mid=(le+ri)>>1;
		build(le,mid,id<<1);build(mid+1,ri,id<<1|1);
	}

	void insert(int le,int ri,int id,line ins){  //le,ri为需要维护的区间,id为线段树区间编号,ins为需要插入的线段
		if(ins.l<=le&&ins.r>=ri){
			if(!seg[id].flag) {seg[id]=ins;seg[id].flag=1;}
			else if((calc(ins,le)-calc(seg[id],le))>eps&&(calc(ins,ri)-calc(seg[id],ri))>eps) {seg[id]=ins;}
			else if((calc(ins,le)-calc(seg[id],le))>eps||(calc(ins,ri)-calc(seg[id],ri))>eps){
				int mid=(le+ri)>>1;
				if(calc(ins,mid)-calc(seg[id],mid)>eps) swap(seg[id],ins);
				if(cross(seg[id],ins)-mid<-eps) insert(le,mid,id<<1,ins);
				else if(cross(seg[id],ins)-mid>eps) insert(mid+1,ri,id<<1|1,ins);
				else{
					if(calc(seg[id],le)<calc(ins,le)) insert(le,mid,id<<1,ins);
					else insert(mid+1,ri,id<<1|1,ins); 
				}
			}
		}else{
			int mid=(le+ri)>>1;
			if(ins.l<=mid) insert(le,mid,id<<1,ins);
			if(ins.r>mid) insert(mid+1,ri,id<<1|1,ins);
		}
	}

	double query(int le,int ri,int id,int pos){ //le,ri表示当前询问的区间
		if(le==ri) return seg[id].flag?calc(seg[id],pos):-inf;
		int mid=(le+ri)>>1;double res=seg[id].flag?calc(seg[id],pos):-inf;
		if(pos<=mid) res=max(res,query(le,mid,id<<1,pos));
		else res=max(res,query(mid+1,ri,id<<1|1,pos));
		return res;
	}
}tree;

int n,pos,l,r;
char opt[100];
double k,b;

int main()
{
	scanf("%d",&n);tree.insert(1,50000,1,line(0,0,1,50000,1));
	while(n--){
		scanf("%s",opt+1);
		if(opt[1]=='P'){
			scanf("%lf %lf",&b,&k);
			tree.insert(1,50000,1,line(k,b-k,1,50000,1));
		}else{
			scanf("%d",&pos);double res=tree.query(1,50000,1,pos);
			printf("%d\n",(int)floor(res/100));
		}
	}
}