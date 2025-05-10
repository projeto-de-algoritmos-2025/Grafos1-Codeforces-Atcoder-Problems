#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define int long long
#define edge tuple<int,int,int>
#define pii pair<int,int>
const int oo = 1e18, mod = 1e9+7; // 998'244'353;
const int MAX = 1.2e6+5;
constexpr array<pair<int, int>, 4> dxy = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

void solve(){
  int n, m, x;
  cin >> n >> m >> x;
  vector<vector<pii>> adj(n);
  for(int i=0; i<m; ++i){
    int u, v;
    cin >> u >> v;
    --u, --v;
    adj[u].emplace_back(v,1);
    adj[v].emplace_back(u,-1);
  }
  int ans=oo;
  vector<vector<int>> dist(n, vector<int>(2,oo)), vis(n, vector<int>(2,0));
  priority_queue<edge, vector<edge>, greater<edge>> heap;
  heap.push({0,0,0});
  heap.push({x,1,0});
  dist[0][1]=x;
  dist[0][0]=0;
  while(heap.size()){
    auto [w,t,u] = heap.top(); heap.pop();
    if(vis[u][t]) continue;
    vis[u][t]=1;
    for(auto &[v,k] : adj[u]){
      int t0;
      if(!t)
        t0 = (~k ? t : t^1ll);
      else
        t0 = (k==-1 ? t : t^1ll);
      if(dist[v][t0]>w+1+(t0==t?0ll:x)){
        dist[v][t0]=w+1+(t0==t?0ll:x);
        heap.push({dist[v][t0],t0,v});
      }
    }
  }
  ans = min(dist[n-1][0],dist[n-1][1]);
  cout << ans << endl;
}



signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t=1;
  // cin >> t;
  for(int i=1; i<=t; ++i)
    solve();
}
