/*codeforces1217F
1.没有该边加入该边，否则删除该边
2.询问u,v是否连通
强制在线做法
*/

#include "bits/stdc++.h"
using namespace std;

struct Xor128 {
    unsigned x, y, z, w;
    Xor128() : x(123456789), y(362436069), z(521288629), w(88675123) {}
    unsigned next() {
        unsigned t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
    }
    inline unsigned next(unsigned n) { return next() % n; }
};

template <typename Node>
struct BottomupTreap {
    Xor128 rng;
    typedef Node *Ref;
    static int size(Ref t) { return !t ? 0 : t->size; }
    unsigned nextRand() { return rng.next(); }
private:
    bool choiceRandomly(Ref l, Ref r) { return l->priority < r->priority; }
public:
    Ref join(Ref l, Ref r) {
        if (!l) return r;
        if (!r) return l;
        Ref t = NULL;
        unsigned long long dirs = 0;
        int h;
        for(h = 0;; ++h) {
            if (h >= sizeof(dirs) * 8 - 2) { t = join(l->right, r->left);dirs = dirs << 2 | 1; h++; break;}
            dirs <<= 1;
            if (choiceRandomly(l, r)) {
                Ref c = l->right;
                if (!c) {t = r; r = r->parent; break; }
                l = c;
            } else {
                dirs |= 1;
                Ref c = r->left;
                if (!c) { t = l; l = l->parent; break; }
                r = c;
            }
        }
        for (; h >= 0; --h) {
            if (!(dirs & 1)) { Ref p = l->parent; t = l->linkr(t); l = p; } 
            else {Ref p = r->parent; t = r->linkl(t); r = p; }
            dirs >>= 1;
        }
        return t;
    }
    typedef pair<Ref, Ref> RefPair;
    RefPair split2(Ref t) {
        Ref p, l = t->left, r = t;
        Node::cut(l);
        t->linkl(NULL);
        while ((p = t->parent)) {
            t->parent = NULL;
            if (p->left == t) r = p->linkl(r);
            else l = p->linkr(l);
            t = p;
        }
        return RefPair(l, r);
    }
    RefPair split3(Ref t) {
        Ref p, l = t->left, r = t->right;
        Node::cut(l), Node::cut(r);
        t->linklr(NULL, NULL);
        while ((p = t->parent)) {
            t->parent = NULL;
            if (p->left == t) r = p->linkl(r);
            else l = p->linkr(l);
            t = p;
        }
        return RefPair(l, r);
    }
    Ref cons(Ref h, Ref t) {
        assert(size(h) == 1);
        if (!t) return h;
        Ref u = NULL;
        while (true) {
            if (choiceRandomly(h, t)) { Ref p = t->parent; u = h->linkr(t); t = p; break; }
            Ref l = t->left;
            if (!l) { u = h; break; }
            t = l;
        }
        while (t) {
            u = t->linkl(u);
            t = t->parent;
        }
        return u;
    }
};

class EulerTourTreeWithMarks {
    struct Node {
        typedef BottomupTreap<Node> BST;
        Node *left, *right, *parent;
        int size;
        unsigned priority;
        char marks, markUnions;
        Node() : left(NULL), right(NULL), parent(NULL), size(1), priority(0), marks(0), markUnions(0) {}
        inline Node *update() {
            int size_t = 1, markUnions_t = marks;
            if (left) {
                size_t += left->size;
                markUnions_t |= left->markUnions;
            }
            if (right) {
                size_t += right->size;
                markUnions_t |= right->markUnions;
            }
            size = size_t, markUnions = markUnions_t;
            return this;
        }

        inline Node *linkl(Node *c) {
            if ((left = c)) c->parent = this;
            return update();
        }
        inline Node *linkr(Node *c) {
            if ((right = c)) c->parent = this;
            return update();
        }
        inline Node *linklr(Node *l, Node *r) {
            if ((left = l)) l->parent = this;
            if ((right = r)) r->parent = this;
            return update();
        }
        static Node *cut(Node *t) {
            if (t) t->parent = NULL;
            return t;
        }

        static const Node *findRoot(const Node *t) {
            while (t->parent) t = t->parent;
            return t;
        }
        static pair<Node *, int> getPosition(Node *t) {
            int k = BST::size(t->left);
            Node *p;
            while ((p = t->parent)) {
                if (p->right == t) k += BST::size(p->left) + 1;
                t = p;
            }
            return make_pair(t, k);
        }
        static const Node *findHead(const Node *t) {
            while (t->left) t = t->left;
            return t;
        }
        static void updatePath(Node *t) {
            while (t) {
                t->update();
                t = t->parent;
            }
        }
    };
    typedef Node::BST BST;
    BST bst;
    vector<Node> nodes;
    vector<int> firstArc;
    vector<bool> edgeMark, vertexMark;
    inline int getArcIndex(const Node *a) const { return a - &nodes[0]; }
    inline int arc1(int ei) const { return ei; }
    inline int arc2(int ei) const { return ei + (numVertices() - 1); }
public:
    inline int numVertices() const { return firstArc.size(); }
    inline int numEdges() const { return numVertices() - 1; }
    inline bool getEdgeMark(int a) const { return a < numEdges() ? edgeMark[a] : false; }
    inline bool getVertexMark(int v) const { return vertexMark[v]; }

private:
    void updateMarks(int a, int v) {
        Node *t = &nodes[a];
        t->marks = getEdgeMark(a) << 0 | getVertexMark(v) << 1;
        Node::updatePath(t);
    }
    void firstArcChanged(int v, int a, int b) {
        if (a != -1) updateMarks(a, v);
        if (b != -1) updateMarks(b, v);
    }

public:
    class TreeRef {
        friend class EulerTourTreeWithMarks;
        const Node *ref;

    public:
        TreeRef() {}
        TreeRef(const Node *ref_) : ref(ref_) {}
        bool operator==(const TreeRef &that) const { return ref == that.ref; }
        bool operator!=(const TreeRef &that) const { return ref != that.ref; }
        bool isIsolatedVertex() const { return ref == NULL; }
    };

    void init(int N) {
        int M = N - 1;
        firstArc.assign(N, -1);
        nodes.assign(M * 2, Node());
        for (int i = 0; i < M * 2; i++) nodes[i].priority = bst.nextRand();
        edgeMark.assign(M, false);
        vertexMark.assign(N, false);
    }

    TreeRef getTreeRef(int v) const {
        int a = firstArc[v];
        return TreeRef(a == -1 ? NULL : Node::findRoot(&nodes[a]));
    }

    bool isConnected(int v, int w) const {
        if (v == w) return true;
        int a = firstArc[v], b = firstArc[w];
        if (a == -1 || b == -1) return false;
        return Node::findRoot(&nodes[a]) == Node::findRoot(&nodes[b]);
    }

    static int getSize(TreeRef t) {
        if (t.isIsolatedVertex()) return 1;
        else return t.ref->size / 2 + 1;
    }

    void link(int ti, int v, int w) {
        int a1 = arc1(ti), a2 = arc2(ti);
        if (v > w) swap(a1, a2);
        int va = firstArc[v], wa = firstArc[w];
        Node *l, *m, *r;
        if (va != -1) {
            pair<Node *, Node *> p = bst.split2(&nodes[va]);
            m = bst.join(p.second, p.first);
        } else {
            m = NULL;
            firstArc[v] = a1;
            firstArcChanged(v, -1, a1);
        }
        if (wa != -1) {
            pair<Node *, Node *> p = bst.split2(&nodes[wa]);
            l = p.first, r = p.second;
        } else {
            l = r = NULL;
            firstArc[w] = a2;
            firstArcChanged(w, -1, a2);
        }
        m = bst.cons(&nodes[a2], m);
        r = bst.cons(&nodes[a1], r);
        bst.join(bst.join(l, m), r);
    }

    void cut(int ti, int v, int w) {
        if (v > w)swap(v, w);
        int a1 = arc1(ti), a2 = arc2(ti);
        pair<Node *, Node *> p = bst.split3(&nodes[a1]);
        int prsize = BST::size(p.second);
        pair<Node *, Node *> q = bst.split3(&nodes[a2]);
        Node *l, *m, *r;
        if (p.second == &nodes[a2] || BST::size(p.second) != prsize) {
            l = p.first, m = q.first, r = q.second;
        }else {
            swap(v, w);swap(a1, a2);
            l = q.first, m = q.second, r = p.second;
        }
        if (firstArc[v] == a1) {
            int b;
            if (r != NULL) b = getArcIndex(Node::findHead(r));
            else b = !l ? -1 : getArcIndex(Node::findHead(l));
            firstArc[v] = b;
            firstArcChanged(v, a1, b);
        }
        if (firstArc[w] == a2) {
            int b = !m ? -1 : getArcIndex(Node::findHead(m));
            firstArc[w] = b;
            firstArcChanged(w, a2, b);
        }

        bst.join(l, r);
    }

    void changeEdgeMark(int ti, bool b) {
        assert(ti < numEdges());
        edgeMark[ti] = b;
        Node *t = &nodes[ti];
        t->marks = (b << 0) | (t->marks & (1 << 1));
        Node::updatePath(t);
    }
    void changeVertexMark(int v, bool b) {
        vertexMark[v] = b;
        int a = firstArc[v];
        if (a != -1) {
            Node *t = &nodes[a];
            t->marks = (t->marks & (1 << 0)) | (b << 1);
            Node::updatePath(t);
        }
    }

    template <typename Callback>
    bool enumMarkedEdges(TreeRef tree, Callback callback) const {
        return enumMarks<0, Callback>(tree, callback);
    }
    template <typename Callback>
    bool enumMarkedVertices(TreeRef tree, Callback callback) const {
        return enumMarks<1, Callback>(tree, callback);
    }

private:
    template <int Mark, typename Callback>
    bool enumMarks(TreeRef tree, Callback callback) const {
        if (tree.isIsolatedVertex())
            return true;
        const Node *t = tree.ref;
        if (t->markUnions >> Mark & 1)
            return enumMarksRec<Mark, Callback>(t, callback);
        else
            return true;
    }
    template <int Mark, typename Callback>
    bool enumMarksRec(const Node *t, Callback callback) const {
        const Node *l = t->left, *r = t->right;
        if (l && (l->markUnions >> Mark & 1)) if (!enumMarksRec<Mark, Callback>(l, callback)) return false;
        if (t->marks >> Mark & 1) if (!callback(getArcIndex(t))) return false;
        if (r && (r->markUnions >> Mark & 1)) if (!enumMarksRec<Mark, Callback>(r, callback)) return false;
        return true;
    }

public:
    void debugEnumEdges(vector<int> &out_v) const {
        int M = numEdges();
        for (int ti = 0; ti < M; ti++) {
            const Node *t = &nodes[ti];
            if (t->left || t->right || t->parent)
                out_v.push_back(ti);
        }
    }
};

class HolmDeLichtenbergThorup {
    typedef HolmDeLichtenbergThorup This;
    typedef EulerTourTreeWithMarks Forest;
    typedef Forest::TreeRef TreeRef;
    int numVertices_m;
    int numSamplings;
    vector<Forest> forests;
    vector<char> edgeLevel;
    vector<int> treeEdgeIndex;         
    vector<int> treeEdgeMap;          
    vector<int> treeEdgeIndexFreeList;  
    vector<int> arcHead;
    vector<vector<int>> firstIncidentArc;
    vector<int> nextIncidentArc, prevIncidentArc;
    vector<bool> edgeVisited;
    vector<int> visitedEdges; 
    int arc1(int ei) const { return ei; }
    int arc2(int ei) const { return numMaxEdges() + ei; }
    int arcEdge(int i) const { return i >= numMaxEdges() ? i - numMaxEdges() : i; }
    bool replace(int lv, int v, int w) {
        Forest &forest = forests[lv];
        TreeRef vRoot = forest.getTreeRef(v), wRoot = forest.getTreeRef(w);
        assert(vRoot.isIsolatedVertex() || wRoot.isIsolatedVertex() || vRoot != wRoot);
        int vSize = forest.getSize(vRoot), wSize = forest.getSize(wRoot);
        int u,uSize;
        TreeRef uRoot;
        if (vSize <= wSize) u = v, uRoot = vRoot, uSize = vSize;
        else u = w, uRoot = wRoot, uSize = wSize;
        int replacementEdge = -1;
        enumIncidentArcs(forest, uRoot, u, lv, FindReplacementEdge(uRoot, &replacementEdge));
        if (replacementEdge != -1 && (int)visitedEdges.size() + 1 <= numSamplings) {
            deleteNontreeEdge(replacementEdge);
            addTreeEdge(replacementEdge);
            for (int i = 0; i < (int)visitedEdges.size(); i++) edgeVisited[visitedEdges[i]] = false;
            visitedEdges.clear();
            return true;
        }
        for (int i = 0; i < (int)visitedEdges.size(); i++) {
            int ei = visitedEdges[i];
            edgeVisited[ei] = false;
            deleteNontreeEdge(ei);
            ++edgeLevel[ei];
            insertNontreeEdge(ei);
        }
        visitedEdges.clear();
        forest.enumMarkedEdges(uRoot, EnumLevelTreeEdges(this));
        for (int i = 0; i < (int)visitedEdges.size(); i++) {
            int ti = visitedEdges[i];
            int ei = treeEdgeMap[ti];
            int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
            int lv = edgeLevel[ei];
            edgeLevel[ei] = lv + 1;
            forests[lv].changeEdgeMark(ti, false);
            forests[lv + 1].changeEdgeMark(ti, true);
            forests[lv + 1].link(ti, v, w);
        }
        visitedEdges.clear();
        if (replacementEdge != -1) {
            deleteNontreeEdge(replacementEdge);
            addTreeEdge(replacementEdge);
            return true;
        }else if (lv > 0) return replace(lv - 1, v, w);
        else return false;
    }

    struct EnumLevelTreeEdges {
        This *thisp;
        EnumLevelTreeEdges(This *thisp_) : thisp(thisp_) {}

        inline bool operator()(int a) {
            thisp->enumLevelTreeEdges(a);
            return true;
        }
    };
    void enumLevelTreeEdges(int ti) { visitedEdges.push_back(ti); }

    template <typename Callback>
    bool enumIncidentArcs(Forest &forest, TreeRef t, int u, int lv, Callback callback) {
        if (t.isIsolatedVertex())
            return enumIncidentArcsWithVertex<Callback>(lv, u, callback);
        else
            return forest.enumMarkedVertices(t, EnumIncidentArcs<Callback>(this, lv, callback));
    }

    template <typename Callback>
    struct EnumIncidentArcs {
        This *thisp;
        int lv;
        Callback callback;
        EnumIncidentArcs(This *thisp_, int lv_, Callback callback_)
            : thisp(thisp_), lv(lv_), callback(callback_) {}
        inline bool operator()(int tii) const {
            return thisp->enumIncidentArcsWithTreeArc(tii, lv, callback);
        }
    };

    template <typename Callback>
    bool enumIncidentArcsWithTreeArc(int tii, int lv, Callback callback) {
        bool dir = tii >= numVertices() - 1;
        int ti = dir ? tii - (numVertices() - 1) : tii;
        int ei = treeEdgeMap[ti];
        int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
        int u = !(dir != (v > w)) ? v : w;
        return enumIncidentArcsWithVertex(lv, u, callback);
    }
    template <typename Callback>
    bool enumIncidentArcsWithVertex(int lv, int u, Callback callback) {
        int it = firstIncidentArc[lv][u];
        while (it != -1) {
            if (!callback(this, it))
                return false;
            it = nextIncidentArc[it];
        }
        return true;
    }

    struct FindReplacementEdge {
        TreeRef uRoot;
        int *replacementEdge;
        FindReplacementEdge(TreeRef uRoot_, int *replacementEdge_)
            : uRoot(uRoot_), replacementEdge(replacementEdge_) {}
        inline bool operator()(This *thisp, int a) const {
            return thisp->findReplacementEdge(a, uRoot, replacementEdge);
        }
    };
    bool findReplacementEdge(int a, TreeRef uRoot, int *replacementEdge) {
        int ei = arcEdge(a);
        if (edgeVisited[ei]) return true;
        int lv = edgeLevel[ei];
        TreeRef hRoot = forests[lv].getTreeRef(arcHead[a]);
        if (hRoot.isIsolatedVertex() || hRoot != uRoot) {
            *replacementEdge = ei;
            return false;
        }
        edgeVisited[ei] = true;
        visitedEdges.push_back(ei);
        return true;
    }

    void addTreeEdge(int ei) {
        int v = arcHead[arc2(ei)], w = arcHead[arc1(ei)];
        int lv = edgeLevel[ei];
        int ti = treeEdgeIndexFreeList.back();
        treeEdgeIndexFreeList.pop_back();
        treeEdgeIndex[ei] = ti;
        treeEdgeMap[ti] = ei;
        forests[lv].changeEdgeMark(ti, true);
        for (int i = 0; i <= lv; i++) forests[i].link(ti, v, w);
    }

    void insertIncidentArc(int a, int v) {
        int ei = arcEdge(a);
        int lv = edgeLevel[ei];
        assert(treeEdgeIndex[ei] == -1);
        int next = firstIncidentArc[lv][v];
        firstIncidentArc[lv][v] = a;
        nextIncidentArc[a] = next;
        prevIncidentArc[a] = -1;
        if (next != -1) prevIncidentArc[next] = a;
        if (next == -1) forests[lv].changeVertexMark(v, true);
    }

    void deleteIncidentArc(int a, int v) {
        int ei = arcEdge(a);
        int lv = edgeLevel[ei];
        assert(treeEdgeIndex[ei] == -1);
        int next = nextIncidentArc[a], prev = prevIncidentArc[a];
        nextIncidentArc[a] = prevIncidentArc[a] = -2;
        if (next != -1) prevIncidentArc[next] = prev;
        if (prev != -1) nextIncidentArc[prev] = next;
        else firstIncidentArc[lv][v] = next;
        if (next == -1 && prev == -1) forests[lv].changeVertexMark(v, false);
    }
    void insertNontreeEdge(int ei) {
        int a1 = arc1(ei), a2 = arc2(ei);
        insertIncidentArc(a1, arcHead[a2]);
        insertIncidentArc(a2, arcHead[a1]);
    }
    void deleteNontreeEdge(int ei) {
        int a1 = arc1(ei), a2 = arc2(ei);
        deleteIncidentArc(a1, arcHead[a2]);
        deleteIncidentArc(a2, arcHead[a1]);
    }
public:
    HolmDeLichtenbergThorup() : numVertices_m(0), numSamplings(0) {}
    int numVertices() const { return numVertices_m; }
    int numMaxEdges() const { return edgeLevel.size(); }
    void init(int N, int M) {
        numVertices_m = N;
        int levels = 1;
        while (1 << levels <= N / 2) levels++;
        numSamplings = (int)(levels * 1);
        forests.resize(levels);
        for (int lv = 0; lv < levels; lv++) forests[lv].init(N);
        edgeLevel.assign(M, -1);
        treeEdgeIndex.assign(M, -1);
        treeEdgeMap.assign(N - 1, -1);
        treeEdgeIndexFreeList.resize(N - 1);
        for (int ti = 0; ti < N - 1; ti++) treeEdgeIndexFreeList[ti] = ti;
        arcHead.assign(M * 2, -1);
        firstIncidentArc.resize(levels);
        for (int lv = 0; lv < levels; lv++) firstIncidentArc[lv].assign(N, -1);
        nextIncidentArc.assign(M * 2, -2);
        prevIncidentArc.assign(M * 2, -2);
        edgeVisited.assign(M, false);
    }

    bool insertEdge(int ei, int v, int w) {
        if (!(0 <= ei && ei < numMaxEdges() && 0 <= v && v < numVertices() && 0 <= w && w < numVertices())) {
            system("pause");
        }
        assert(0 <= ei && ei < numMaxEdges() && 0 <= v && v < numVertices() && 0 <= w && w < numVertices());
        assert(edgeLevel[ei] == -1);
        int a1 = arc1(ei), a2 = arc2(ei);
        arcHead[a1] = w, arcHead[a2] = v;
        bool treeEdge = !forests[0].isConnected(v, w);
        edgeLevel[ei] = 0;
        if (treeEdge) addTreeEdge(ei);
        else {
            treeEdgeIndex[ei] = -1;
            if (v != w) insertNontreeEdge(ei);
        }
        return treeEdge;
    }

    bool deleteEdge(int ei) {
        assert(0 <= ei && ei < numMaxEdges() && edgeLevel[ei] != -1);
        int a1 = arc1(ei), a2 = arc2(ei);
        int v = arcHead[a2], w = arcHead[a1];
        int lv = edgeLevel[ei];
        int ti = treeEdgeIndex[ei];
        bool splitted = false;
        if (ti != -1) {
            treeEdgeMap[ti] = -1;
            treeEdgeIndex[ei] = -1;
            treeEdgeIndexFreeList.push_back(ti);
            for (int i = 0; i <= lv; i++) forests[i].cut(ti, v, w);
            forests[lv].changeEdgeMark(ti, false);
            splitted = !replace(lv, v, w);
        }else if(v != w) deleteNontreeEdge(ei);
        arcHead[a1] = arcHead[a2] = -1;
        edgeLevel[ei] = -1;
        return splitted;
    }

    bool isConnected(int v, int w) const { return forests[0].isConnected(v, w); }
};
vector<int> te;
map<int, map<int, int>> ee;
map<pair<int,int>,int> memor;
int lastans = 0,n,m,opt,u,v;
int main() {
    scanf("%d %d",&n,&m);
    for (int i = m; i > 0; --i) te.push_back(i);
    typedef HolmDeLichtenbergThorup FullyDynamicConnectivity;
    FullyDynamicConnectivity fdc;
    fdc.init(n + 1, m + 1);
    while(m--){
        scanf("%d %d %d",&opt,&u,&v);
        u=(u+lastans-1)%n+1;
        v=(v+lastans-1)%n+1;
        if(u>v) swap(u,v);
        if(opt==1) {
            if(memor.count(make_pair(u,v))) { //该边存在的时候删边 
                fdc.deleteEdge(ee[u][v]);
                ee[u].erase(v);
                memor.erase(make_pair(u,v));
            }else {                           //不存在的时候加入边
                ee[u][v] = te.back();
                te.pop_back();
                fdc.insertEdge(ee[u][v], u, v);
                memor[make_pair(u,v)]=1;
            }
        }else {                             //查询u,v是否连通
            lastans=fdc.isConnected(u,v);
            printf("%c",'0'+lastans);
        }
    }
    return 0;
}