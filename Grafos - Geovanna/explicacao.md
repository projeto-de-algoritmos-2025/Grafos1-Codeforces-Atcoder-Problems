# Grafos Parte 1

## E - Third Avenue

Problema do AtCoder: [https://atcoder.jp/contests/abc184/tasks/abc184_e](https://atcoder.jp/contests/abc184/tasks/abc184_e)

### Explicação da solução: 
BFS numa matriz 2D, em que cada nó que representa uma letra é um portal para um nó de mesma letra, com custo 1 toda vez q visitar uma letra pela primeira vez, vc marca a distância+1 pra cada nó de mesma letra e distância menor e marca que visitou aquela letra. Ao final, só retornar a menor distância até G.

## Código submetido:

```cpp
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
  int h, w;
  cin >> h >> w;
  pii s, g;
  vector<vector<char>> grid(h+2, vector<char>(w+2,'#'));
  map<char,vector<pii>> adj;
  for(int i=1; i<=h; ++i){
    for(int j=1; j<=w; ++j){
      cin >> grid[i][j];
      if(grid[i][j]=='S') s = pii(i,j);
      if(grid[i][j]=='G') g = pii(i,j);
      if(grid[i][j]!='.') adj[grid[i][j]].push_back(pii(i,j));
    }
  }
  queue<pii> qs;
  vector<vector<int>> dist(h+2, vector<int>(w+2,oo)), vis(h+2, vector<int>(w+2,0));
  dist[s.first][s.second]=0;
  qs.push({s.first,s.second});
  map<char,int> mp;
  while(qs.size()){
    auto [i,j] = qs.front(); qs.pop();
    if(vis[i][j]) continue;
    vis[i][j]=1;
    for(auto &[x,y] : dxy){
      int u = i+x, v = j+y;
      if(grid[u][v]!='#' && dist[i][j]+1<dist[u][v]){
      	dist[u][v] = dist[i][j]+1;
      	qs.push({u,v});
      }
    }
    if(!mp[grid[i][j]]){
      for(auto &[a,b] : adj[grid[i][j]]){
        dist[a][b]=min(dist[a][b],dist[i][j]+1);
        qs.push({a,b});
      }
    }
    mp[grid[i][j]]=1;
  }
  cout << (dist[g.first][g.second]>=oo ? -1 : dist[g.first][g.second])  << endl;
}


signed main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int t=1;
  // cin >> t;
  for(int i=1; i<=t; ++i)
    solve();
}
```
