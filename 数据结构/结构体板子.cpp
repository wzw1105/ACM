struct node{
    int a,b;
    node(){};
    node(int x,int y){a=x;b=y;}
    bool operator < (const node &other) const {
        return a!=other.a?a < other.a:b<other.b; //��priority_queue�Ļ��Ǹ��󶥶ѣ�������� 
    }
};
