#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define int long long
#define edge tuple<int,int,int>
#define pii pair<int,int>
const int oo = 2e18, mod = 998'244'353;
const int MAX = 2e5+20;
constexpr array<pair<int, int>, 4> dxy = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

void solve(){
  int n, k;
  cin >> n >> k;
  vector<int> as(n), mx(n,-1);
  for(auto &x : as) cin >> x;
  vector<vector<int>> adj(n);
  while(k--){
    int u, v;
    cin >> u >> v;
    --u, --v;
    adj[u].push_back(v);
  }
  int ans=-oo;
  bitset<MAX> vis;
  auto dfs = [&](auto &&self, int u) -> void {
    if(vis[u]) return;
    vis[u]=1;
    for(auto &x : adj[u]){
      self(self, x);
      mx[u]=max(mx[u],mx[x]);
      ans=max(ans,mx[x]-as[u]);
    }
    mx[u]=max(mx[u],as[u]);
  };
  for(int i=0; i<n; ++i){
    dfs(dfs, i);
  }
  cout << ans << endl;
}


signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int t=1;
  // cin >> t;
  for(int i=1; i<=t; ++i)
    solve();
}

