# Grafos Parte 1

## Third Avenue

Problema no AtCoder: [https://atcoder.jp/contests/abc184/tasks/abc184_e](https://atcoder.jp/contests/abc184/tasks/abc184_e)

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

## Peddler

Problema no AtCoder: [https://atcoder.jp/contests/abc188/tasks/abc188_e](https://atcoder.jp/contests/abc188/tasks/abc188_e)

### Explicação da solução: 
Trata-se de uma busca em profundidade (DFS) convencional, na qual é mantido o menor valor encontrado até o momento, sendo atualizado conforme são visitados nós com valores inferiores. O maior valor associado a cada nó é armazenado em um vetor auxiliar. A resposta é computada da seguinte forma: para cada nó ii, atualiza-se mx[i]=max⁡(mx[i],mx[j])mx[i]=max(mx[i],mx[j]), onde jj representa cada filho de ii. Ao final, a resposta global é determinada por ans=max⁡(ans,mx[i]−min_atual)ans=max(ans,mx[i]−min_atual).

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
```

## Palindromic Shortest Path

Problema no AtCoder: [https://atcoder.jp/contests/abc394/tasks/abc394_e](https://atcoder.jp/contests/abc394/tasks/abc394_e)

### Explicação da solução: 
O problema consiste em encontrar o menor caminho em que os vértices formam um palíndromo, e a abordagem utilizada é uma busca em largura (BFS). A distância é zero quando o nó parte para ele mesmo, e é igual a um nos casos em que o caminho é composto por um único caractere. Durante o processo de busca, para cada par de nós visitados, realiza-se uma verificação de complexidade quadrática com o objetivo de identificar a existência de um nó intermediário XX que seja acessível a partir de ambos, e cujas arestas de ida e volta possuam o mesmo rótulo, desde que esse rótulo não seja nulo (ou seja, diferente de "-").

## Código submetido:

```cpp
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
```