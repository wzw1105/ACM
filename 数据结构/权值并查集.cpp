#include<iostream>
#include<cstdio>  //POJ食物链

using namespace std;
const int maxn = 100005;

int n, m, d, u, v, ans = 0, fa[maxn], val[maxn];

void init(int k) {for(int i = 1; i <= k; i++) fa[i] = i, val[i] = 0;}
int fin(int cur) {
    if(fa[cur] == cur) return cur;
    int root = fin(fa[cur]);
    val[cur] += val[fa[cur]];
    return fa[cur] = root;
}
void unite(int d, int u, int v) {
    int x = fin(u), y = fin(v);
    if(d == 1) {
        if(x == y && (val[u] - val[v]) % 3 != 0) ans++;
        else if(x != y) {
            val[x] += 3 - (((val[u] - val[v]) % 3 + 3) % 3);
            fa[x] = y;
        }
    }
    else {
        if(x == y && (((val[u] - val[v]) % 3 + 3) % 3) != 1) ans++;
        else if(x != y) {
            val[x] += 4 - (((val[u] - val[v]) % 3 + 3) % 3);
            fa[x] = y;
        }
    }
}
int main() {
    scanf("%d %d", &n, &m);
    init(n);
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &d, &u, &v);
        if(u > n || v > n || u < 1 || u < 1 || (d == 2 && u == v)) {
            ans++;
            continue;
        }
        unite(d, u, v);
    }
    printf("%d\n", ans);
}