struct node{
    int a,b;
    node(){};
    node(int x,int y){a=x;b=y;}
    bool operator < (const node &other) const {
        return a!=other.a?a < other.a:b<other.b; //放priority_queue的话是个大顶堆，大的优先 
    }
};
