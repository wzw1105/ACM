#include<bits/stdc++.h>
using namespace std;

void update(int &fir,int &sec,int val) {//插入val维护最大次大值
	if(val>=fir)     {sec=fir;fir=val;}
	else if(val>sec) {sec=val;}
}
int get(int &fir,int &sec,int val) {  //查询除去值val的情况下的最大值
	if(val==fir) return sec;
	else return fir;
}
void update(int &fir,int &sec,int &thi,int val) { //插入val维护最大的三个值
	if(val>=fir)      {thi=sec;sec=fir;fir=val;}
	else if(val>=sec) {thi=sec;sec=val;}
	else if(val>thi)  {thi=val;}
}
int get(int &fir,int &sec,int &thi,int val) {//查询除去值val的情况下的最大值与次大值之和
	if(val==fir) return sec+thi;
	else if(val==sec) return fir+thi;
	else return fir+sec;
}
