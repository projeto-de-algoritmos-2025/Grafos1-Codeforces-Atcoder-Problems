#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int MAX = 2e5+10, oo=2e9+7;
const int mod = 998'244'353;
using edge = tuple<int, int, int>;

class dsu {
  public:
    dsu() : _n(0) {}
    explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    vector<vector<int>> groups() {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

  private:
    int _n;
    // root node: -1 * component size
    // otherwise: parent
    vector<int> parent_or_size;
};

void kruskal(int N, vector<pair<edge,int>>& es, vector<string>& ans){
    sort(es.begin(), es.end());
    dsu ufds(MAX);
    for(auto k : es){
        auto [w,u,v] = k.first;
        int p = k.second;
        if(p<0){
            if(!ufds.same(u, v))
                ufds.merge(u, v);
        }
        else if(!ufds.same(u,v))
            ans[p]="Yes";
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    vector<edge> es(m);
    for(int i=0; i<m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        es[i] = {c,a,b};
    }
    vector<string> ans(q, "No");
    vector<pair<edge,int>> qs(q);
    for(int i=0; i<q; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        qs[i] = {{c,a,b},i};
    }
    vector<pair<edge,int>> res(m+q);
    for(int i=0; i<m; ++i)
        res[i] = {{es[i]},-1};
    for(int i=0; i<q; ++i)
        res[i+m] = qs[i];
    kruskal(n, res, ans);
    for(auto x : ans)
        cout << x << '\n';
}