#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define int long long
#define edge tuple<int,int,int>
#define pii pair<int,int>
const int oo = 1e15, mod = 1e9+7; // 998'244'353;
const int MAX = 1.2e6+5;
constexpr array<pair<int, int>, 4> dxy = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

void solve(){
  int h, w, si, sj;
  cin >> h >> w;
  vector<vector<char>> grid(h, vector<char>(w));
  vector<vector<int>> dist(h, vector<int>(w,-1)), vis(h, vector<int>(w,0));
  for(int i=0; i<h; ++i) for(int j=0; j<w; ++j){
    cin >> grid[i][j];
    if(grid[i][j]=='S') si=i, sj=j;
  }
  priority_queue<edge> heap;
  dist[si][sj]=0;
  auto check = [&](int x, int y) -> bool {
    return x>=0 && x<h && y>=0 && y<w && grid[x][y]!='#';
  };
  for(auto &[dx,dy] : dxy){
    int x = dx+si, y = dy+sj;
    if(check(x,y)){
      dist[x][y]=1;
      heap.push({1,x,y});
    }
  }
  while(heap.size()){
    auto [W, i, j] = heap.top(); heap.pop();
    if(vis[i][j]) continue;
    vis[i][j]=1;
    for(const auto &[dx, dy] : dxy){
      int x = i+dx, y = j+dy;
      if(x==si && y==sj && W==1) continue;
      if(check(x, y) && dist[x][y]<W+1){
        dist[x][y]=W+1;
        heap.push({W+1,x,y});
      }
    }
  }
  cout << (dist[si][sj]>=4 ? "Yes" : "No" ) << endl;
}


signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t=1;
  // cin >> t;
  for(int i=1; i<=t; ++i)
    solve();
}
