#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int MAX = 1e6+10, oo=1e9+10;

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
    vector<int> parent_or_size;
};

struct parent {
    int l, s, c;
};

void solve(){
    int n, q;
    cin >> n >> q;
    vector<parent> ps(n+2, {-1,-1,-1});
    vector<int> cnt(n+2, 1);
    for(int i=1; i<=n; ++i)
        ps[i] = {i,1,i};
    dsu d(n+2);
    while(q--){
        int t, x, c;
        cin >> t;
        if(t==1){
            cin >> x >> c;

            int now = d.leader(x);
            int l = ps[now].l, s = ps[now].s, last = ps[now].c;

            cnt[last]-=s;
            cnt[c]+=s;
            int nxt_l = d.leader(l-1), nxt_r = d.leader(l+s);

            if(ps[nxt_l].c==c){
                d.merge(l-1,x);
                l = ps[nxt_l].l;
                s += ps[nxt_l].s;
            }
            if(ps[nxt_r].c==c){
                d.merge(l+s,x);
                s += ps[nxt_r].s;
            }
            
            ps[d.leader(x)] = {l,s,c};
        }
        else{
            cin >> c;
            cout << cnt[c] << endl;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t=1;
    for(int i=1; i<=t; ++i)
        solve();
}