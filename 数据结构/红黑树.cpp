#include <cstdio>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;

template<typename T> class redblacktree {
    private:
        struct Node;

        Node* _root;    ////根节点位置
        Node* _hot; ////临时维护的节点

        void init(T);
        void connect34(Node*, Node*, Node*, Node*, Node*, Node*, Node*);
        void SolveDoubleRed(Node*); ////双红修正
        void SolveDoubleBlack(Node*);   //双黑修正
        Node* find(T, const int);   ////允许重复的查找
        Node* rfind(T, const int);  ////不允许重复的查找
        Node* findkth(int, Node*);
        int find_rank(T, Node*);

        void checkconnect(Node*);
        void previs(Node*, int);
        void invis(Node*, int);
        void postvis(Node*, int);
        void erase_node(Node*);

    public:
        redblacktree() : _root(NULL), _hot(NULL) {}
        struct iterator;
        iterator begin();
        iterator end();
        iterator rbegin();
        iterator rend();
        
        int rank(T);
        iterator insert(T);
        bool erase(T);
        int size();
        bool empty();
        iterator kth(int);   //返回第k大的迭代器
        iterator pre(T);   //小于T的最大的元素，即前驱
        iterator next(T);   //大于T的最小的元素，即后继
        void clear();

        void vis();
        void correctlyconnected();
};

template <typename T>
struct redblacktree<T>::Node {
    T val;  ////节点信息
    bool RBc;   ////节点颜色，若为true，则节点为Red;否则节点为Black.
    Node* fa;  ////父亲
    Node* ls;   ////左儿子
    Node* rs;   ////右儿子
    int s;      ////域

    friend Node* bro(Node* x){
        return (((x)->fa->ls == (x)) ? ((x)->fa->rs) : ((x)->fa->ls));
    }
    friend bool isls(Node* x){
        return ((x) != NULL && (x->fa) != NULL && (x)->fa->ls == (x));
    }
    friend bool isrs(Node* x){
        return ((x) != NULL && (x->fa) != NULL && (x)->fa->rs == (x));
    }

    Node(   T v = T(), bool RB = true,
            Node* f = NULL, Node* l = NULL, Node* r = NULL ,int ss = 1  )
        : val(v), RBc(RB), fa(f), ls(l), rs(r), s(ss) {}

    Node* succ() {      ////删除节点时用到的替代节点
        Node* ptn = rs;
        while(ptn->ls != NULL) {
            --(ptn->s);
            ptn = ptn->ls;
        }
        return ptn;
    }

    Node* left_node() {     ////直接前驱
        Node* ptn = this;
        if(ptn->ls) {
            ptn=ptn->ls;
            while(ptn->rs) ptn=ptn->rs;
        }
        else if(isrs(ptn)) ptn=ptn->fa;
        else{
            ptn=ptn->fa;
            while(ptn){
                if(isrs(ptn)){
                    ptn=ptn->fa;
                    break;
                }
                ptn=ptn->fa;
            }
        }
        return ptn;
    }

    Node* right_node() {    ////直接后继
        Node* ptn = this;
        if(ptn->rs) {
            ptn=ptn->rs;
            while(ptn->ls) ptn=ptn->ls;
        }
        else if(isls(ptn)) ptn=ptn->fa;
        else{
            ptn=ptn->fa;
            while(ptn){
                if(isls(ptn)){
                    ptn=ptn->fa;
                    break;
                }
                ptn=ptn->fa;
            }
        }
        return ptn;
    }

    void maintain() {   ////维护域s
        s = 1;
        if(ls) s += ls->s;
        if(rs) s += rs->s;
    }
};

template <typename T>
struct redblacktree<T>::iterator {
    private:
        Node* _real__node;
    public:
        iterator& operator++() {
            _real__node = _real__node->right_node();
            return *this;
        }

        iterator& operator--() {
            _real__node = _real__node->left_node();
            return *this;
        }

        const iterator operator++(int){
            iterator tmp=*this;
            _real__node=_real__node->right_node();
            return tmp;
        }
        const iterator operator--(int){
            iterator tmp=*this;
            _real__node=_real__node->left_node();
            return tmp;
        }

        bool operator!=(const iterator &other){
            return _real__node!=other._real__node;
        }

        T operator*() {
            return _real__node->val;
        }

        iterator(Node* node_nn = NULL) : _real__node(node_nn) {}
        iterator(iterator const& iter) : _real__node(iter._real__node) {}

};

template<typename T>
typename redblacktree<T>::iterator redblacktree<T>::begin(){
    Node* ptn=_root;
    while(ptn->ls) ptn=ptn->ls;
    return ptn;
}

template<typename T>
typename redblacktree<T>::iterator redblacktree<T>::end(){
    return iterator(NULL);
}

template<typename T>
typename redblacktree<T>::iterator redblacktree<T>::rbegin(){
    Node* ptn=_root;
    while(ptn->rs) ptn=ptn->rs;
    return ptn;
}

template<typename T>
typename redblacktree<T>::iterator redblacktree<T>::rend(){
    return iterator(NULL);
}

template <typename T> 
typename redblacktree<T>::iterator redblacktree<T>::insert(T v) {
    Node* ptn = find(v, 1);
    if(_hot == NULL) {
        init(v);
        return iterator(_root);
    }
    ptn = new Node(v, true, _hot, NULL, NULL, 1);
    if( _hot->val <= v  ) _hot->rs = ptn;
    else _hot->ls = ptn;
    SolveDoubleRed(ptn);
    return iterator(ptn);
    /*Node* ptn=rfind(v,1);
    if(_hot==NULL&&ptn==NULL) {
        init(v);
        return iterator(_root);
    }else if(ptn==NULL){
        ptn = new Node(v, true, _hot, NULL, NULL, 1);
        if( _hot->val <= v  ) _hot->rs = ptn;
        else _hot->ls = ptn;
        SolveDoubleRed(ptn);
        return iterator(ptn);
    }else return iterator(ptn);*/
}

template <typename T>
void redblacktree<T>::init(T v) {
    _root = new Node(v, false, NULL, NULL, NULL, 1);
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::find(T v, const int op) {
    Node* ptn = _root;  ////从根节点开始查找
    _hot = NULL;    ////维护父亲节点
    while(ptn != NULL) {
        _hot = ptn;
        ptn->s += op;
        if(ptn->val > v) ptn = ptn->ls;
        else ptn = ptn->rs;
    }
    return ptn;
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::rfind(T v, const int op) {
    Node* ptn = _root;
    _hot = NULL;
    while(ptn != NULL && ptn->val != v) {
        _hot = ptn;
        ptn->s += op;
        if(ptn->val > v) ptn = ptn->ls;
        else ptn = ptn->rs;
    }
    return ptn;
}

template <typename T>
void redblacktree<T>::SolveDoubleRed(Node* nn) {
    while((!(nn->fa)) || nn->fa->RBc) {
        if(nn == _root) {
            _root->RBc = false;
            return;
        }
        Node* pfa = nn->fa;
        if(!(pfa->RBc)) return;            ////No double-red
        Node* uncle = bro(nn->fa);
        Node* grdfa = nn->fa->fa;
        if(uncle != NULL && uncle->RBc) {   ////RR-2
            grdfa->RBc = true;
            uncle->RBc = false;
            pfa->RBc = false;
            nn = grdfa;
        } else {                            ////RR-1
            if(isls(pfa)) {
                if(isls(nn)) {
                    pfa->fa = grdfa->fa;
                    if(grdfa == _root) _root = pfa;
                    else if(grdfa->fa->ls == grdfa) grdfa->fa->ls = pfa;
                    else grdfa->fa->rs = pfa;
                    connect34(pfa, nn, grdfa, nn->ls, nn->rs, pfa->rs, uncle);
                    pfa->RBc = false;
                    grdfa->RBc = true;
                } else {
                    nn->fa = grdfa->fa;
                    if(grdfa == _root) _root = nn;
                    else if(grdfa->fa->ls == grdfa) grdfa->fa->ls = nn;
                    else grdfa->fa->rs = nn;
                    connect34(nn, pfa, grdfa, pfa->ls, nn->ls, nn->rs, uncle);
                    nn->RBc = false;
                    grdfa->RBc = true;
                }
            } else {
                if(isls(nn)) {
                    nn->fa = grdfa->fa;
                    if(grdfa == _root) _root = nn;
                    else if(grdfa->fa->ls == grdfa) grdfa->fa->ls = nn;
                    else grdfa->fa->rs = nn;
                    connect34(nn, grdfa, pfa, uncle, nn->ls, nn->rs, pfa->rs);
                    nn->RBc = false;
                    grdfa->RBc = true;
                } else {
                    pfa->fa = grdfa->fa;
                    if(grdfa == _root) _root = pfa;
                    else if(grdfa->fa->ls == grdfa) grdfa->fa->ls = pfa;
                    else grdfa->fa->rs = pfa;
                    connect34(pfa, grdfa, nn, uncle, pfa->ls, nn->ls, nn->rs);
                    pfa->RBc = false;
                    grdfa->RBc = true;
                }
            }
            return;
        }
    }
}
template <typename T>
void redblacktree<T>::connect34(    Node* nroot,    Node* nls,      Node* nrs,
                                    Node* ntree1,   Node* ntree2,   Node* ntree3,   Node* ntree4) {
    nls->ls = ntree1;
    if(ntree1 != NULL) ntree1->fa = nls;
    nls->rs = ntree2;
    if(ntree2 != NULL) ntree2->fa = nls;
    nrs->ls = ntree3;
    if(ntree3 != NULL) ntree3->fa = nrs;
    nrs->rs = ntree4;
    if(ntree4 != NULL) ntree4->fa = nrs;
    nroot->ls = nls;
    nls->fa = nroot;
    nroot->rs = nrs;
    nrs->fa = nroot;
    nls->maintain();
    nrs->maintain();
    nroot->maintain();
}
template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::pre(T v) {
    Node* ptn = _root;
    while(ptn) {
        _hot = ptn;
        if(ptn->val < v) ptn = ptn->rs;
        else ptn = ptn->ls;
    }
    if(_hot->val < v) ptn = _hot;
    else ptn = _hot->left_node();
    return iterator(ptn);
}
template <typename T>
typename redblacktree<T>::iterator redblacktree<T>::next(T v) {
    Node* ptn = _root;
    while(ptn) {
        _hot = ptn;
        if(ptn->val > v) ptn = ptn->ls;
        else ptn = ptn->rs; 
    }
    if(_hot->val > v) ptn = _hot;
    else ptn = _hot->right_node();
    return iterator(ptn);
}
template <typename T>
typename
redblacktree<T>::iterator redblacktree<T>::kth(int rank) {
    return iterator(findkth(rank, _root));
}

template <typename T>
typename
redblacktree<T>::Node* redblacktree<T>::findkth(int rank, Node* ptn) {
    if(!(ptn->ls)) {
        if(rank == 1) {
            return ptn;
        } else {
            return findkth(rank - 1, ptn->rs);
        }
    } else {
        if(ptn->ls->s == rank - 1) return ptn;
        else if(ptn->ls->s >= rank) return findkth(rank, ptn->ls);
        else return findkth(rank - (ptn->ls->s) - 1, ptn->rs);
    }
}

template <typename T>
void redblacktree<T>::clear()
{
    erase(_root);
    _root=NULL;_hot=NULL;
}

template <typename T>
void redblacktree<T>::erase_node(Node* cur)
{
    if(cur==NULL) return;
    erase_node(cur->ls);erase_node(cur->rs);
    delete cur;
}

template <typename T>
int redblacktree<T>::rank(T v) {
    return find_rank(v, _root);
}

template <typename T>
int redblacktree<T>::find_rank(T v, Node* ptn) {
    if(!ptn) return 1;
    else if(ptn->val >= v) return find_rank(v, ptn->ls);
    else return (1 + ((ptn->ls) ? (ptn->ls->s) : 0) + find_rank(v, ptn->rs));
    /*if(!ptn) return 1;
    if(ptn->val > v) return find_rank(v, ptn->ls);
    else if(ptn->val == v) return 1 + ((ptn->ls) ? (ptn->ls->s) : 0);
    else return (((ptn->s)-((ptn->rs)?(ptn->rs->s):0)) + find_rank(v, ptn->rs));*/
}

template <typename T>
int redblacktree<T>::size() {
    if(_root==NULL) return 0;
    return _root->s;
}

template <typename T>
bool redblacktree<T>::empty() {
    return !_root;
}

template <typename T>
bool redblacktree<T>::erase(T v) {
    Node* ptn = rfind(v, -1);
    if(!ptn) return false;
    Node* node_suc;
    while(ptn->ls || ptn->rs) { ////迭代寻找真后继
        if(!(ptn->ls)) {
            node_suc = ptn->rs;
        } else if(!(ptn->rs)) {
            node_suc = ptn->ls;
        } else {
            node_suc = ptn->succ();
        }
        --(ptn->s);
        ptn->val = node_suc->val;
        ptn = node_suc;
    }
    if(!(ptn->RBc)) {
        --(ptn->s);
        SolveDoubleBlack(ptn);
    }
    if(ptn == _root) {
        _root = NULL;
        delete ptn;
        return true;
    }
    if(ptn->fa->ls == ptn)
        ptn->fa->ls = NULL;
    else
        ptn->fa->rs = NULL;
    delete ptn;
    return true;
}

template <typename T>
void redblacktree<T>::SolveDoubleBlack(Node* nn) {
    while(nn != _root) {
        Node* pfa = nn->fa;
        Node* bthr = bro(nn);
        if(bthr->RBc) {                 ////BB-1
            bthr->RBc = false;
            pfa->RBc = true;
            if(_root == pfa) _root = bthr;
            if(pfa->fa) {
                if(pfa->fa->ls == pfa)
                    pfa->fa->ls = bthr;
                else
                    pfa->fa->rs = bthr;
            }
            bthr->fa = pfa->fa;
            if(isls(nn)) {
                connect34(bthr, pfa, bthr->rs, nn, bthr->ls, bthr->rs->ls, bthr->rs->rs);
            } else {
                connect34(bthr, bthr->ls, pfa, bthr->ls->ls, bthr->ls->rs, bthr->rs, nn);
            }
            bthr = bro(nn);
            pfa = nn->fa;
        }
        if(bthr->ls && bthr->ls->RBc) { ////BB-3
            bool oldRBc = pfa->RBc;
            pfa->RBc = false;
            if(pfa->ls == nn) {
                if(pfa->fa) {
                    if(pfa->fa->ls == pfa)
                        pfa->fa->ls = bthr->ls;
                    else
                        pfa->fa->rs = bthr->ls;
                }
                bthr->ls->fa = pfa->fa;
                if(_root == pfa) _root = bthr->ls;
                connect34(bthr->ls, pfa, bthr, pfa->ls, bthr->ls->ls, bthr->ls->rs, bthr->rs);
            } else {
                bthr->ls->RBc = false;
                if(pfa->fa) {
                    if(pfa->fa->ls == pfa)
                        pfa->fa->ls = bthr;
                    else
                        pfa->fa->rs = bthr;
                }
                bthr->fa = pfa->fa;
                if(_root == pfa) _root = bthr;
                connect34(bthr, bthr->ls, pfa, bthr->ls->ls, bthr->ls->rs, bthr->rs, pfa->rs);
            }
            pfa->fa->RBc = oldRBc;
            return;
        } else if(bthr->rs && bthr->rs->RBc) {  ////BB-3
            bool oldRBc = pfa->RBc;
            pfa->RBc = false;
            if(pfa->ls == nn) {
                bthr->rs->RBc = false;
                if(pfa->fa) {
                    if(pfa->fa->ls == pfa)
                        pfa->fa->ls = bthr;
                    else
                        pfa->fa->rs = bthr;
                }
                bthr->fa = pfa->fa;
                if(_root == pfa) _root = bthr;
                connect34(bthr, pfa, bthr->rs, pfa->ls, bthr->ls, bthr->rs->ls, bthr->rs->rs);
            } else {
                if(pfa->fa) {
                    if(pfa->fa->ls == pfa)
                        pfa->fa->ls = bthr->rs;
                    else
                        pfa->fa->rs = bthr->rs;
                }
                bthr->rs->fa = pfa->fa;
                if(_root == pfa) _root = bthr->rs;
                connect34(bthr->rs, bthr, pfa, bthr->ls, bthr->rs->ls, bthr->rs->rs, pfa->rs);
            }
            pfa->fa->RBc = oldRBc;
            return;
        }
        if(pfa->RBc) {                 ////BB-2R
            pfa->RBc = false;
            bthr->RBc = true;
            return;
        } else {                        ////BB-2B
            bthr->RBc = true;
            nn = pfa;
        }
    }
}

template <typename T>   ////先序遍历
void redblacktree<T>::previs(Node* ptn, int cnt) {
    if(ptn == NULL) return;
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
    if(!(ptn->RBc)) ++cnt;
    previs(ptn->ls, cnt);
    previs(ptn->rs, cnt);
}

template <typename T>   ////中序遍历
void redblacktree<T>::invis(Node* ptn, int cnt) {
    if(ptn == NULL) return;
    if(!(ptn->RBc)) ++cnt;
    invis(ptn->ls, cnt);
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
    invis(ptn->rs, cnt);
}

template <typename T>   ////后序遍历
void redblacktree<T>::postvis(Node* ptn, int cnt) {
    if(ptn == NULL) return;
    if(!(ptn->RBc)) ++cnt;
    postvis(ptn->ls, cnt);
    postvis(ptn->rs, cnt);
    printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
}

template <typename T>   ////输出所有序遍历的接口
void redblacktree<T>::vis() {
    printf("------pre-vis------\n");
    previs(_root, 0);
    printf("------in-vis------\n");
    invis(_root, 0);
    printf("------post-vis------\n");
    postvis(_root, 0);
}

template <typename T>   ////验证所有节点与父亲的连接是否正常、域s是否维护正常
void redblacktree<T>::checkconnect(Node* ptn) {
    if(!ptn) return;
    assert(ptn->s > 0);
    if(ptn->ls && ptn->ls->fa != ptn) {
        printf("Oops! %d has a ls %d, but it failed to point its fa!\n", ptn->val, ptn->ls->val);
    }
    if(ptn->rs && ptn->rs->fa != ptn) {
        printf("Oops! %d has a rs %d, but it failed to point its fa!\n", ptn->val, ptn->rs->val);
    }
    int sss = ptn->s;
    if(ptn->ls) sss -= ptn->ls->s;
    if(ptn->rs) sss -= ptn->rs->s;
    if(sss - 1) {
        printf("Damn! %d's size is %d, but the sum of its children's size is %d!\n", ptn->val, ptn->s, ptn->s - sss);
    }
    checkconnect(ptn->ls);
    checkconnect(ptn->rs);
}

template <typename T>
void redblacktree<T>::correctlyconnected() {
    checkconnect(_root);
}

redblacktree<int> tree;
int n,a,m,l,r,opt;
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d %d",&opt,&a);
        if(opt==1) tree.insert(a);
        else if(opt==2) tree.erase(a);
        else if(opt==3) printf("%d\n",tree.rank(a));
        else if(opt==4) printf("%d\n",*tree.kth(a));
        else if(opt==5) printf("%d\n",*tree.pre(a));
        else printf("%d\n",*tree.next(a));
    }
}