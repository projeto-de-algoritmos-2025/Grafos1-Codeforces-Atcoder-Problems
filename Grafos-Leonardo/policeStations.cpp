#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> graph;

void bfs(graph& G, vector<int> ps, int d, vector<bool>& visited, vector<pair<int,int>>& E, vector<bool>& maintainE, vector<bool>& is_p, vector<int>& indexes){
    queue<pair<int,int>> q;
    for(int p: ps){{}
        q.push({p, 0});
        visited[p] = true;
    }
    while(!q.empty()){
        pair<int,int> u = q.front();
        q.pop();
        if(u.second + 1 > d)
            continue;
        for(int adj: G[u.first]){
            if(!visited[adj] && !is_p[adj]){
                visited[adj] = true;
                pair<int,int> pp;
                if(adj < u.first)
                    pp = {adj, u.first};
                else
                    pp = {u.first, adj};
                int ind = lower_bound(E.begin(), E.end(), pp) - E.begin();
                maintainE[indexes[ind]] = true;
                q.push({adj, u.second + 1});    
            }
        }
    }
}


vector<bool> solve(vector<pair<int,int>>& E, graph& G, vector<int> ps, int d){
    vector<pair<int,int>> sortE = E;
    sort(sortE.begin(), sortE.end());
    vector<int> indexes(E.size());
    for(int i = 0; i < E.size(); i++){
        int place = lower_bound(sortE.begin(), sortE.end(), E[i]) - sortE.begin();
        indexes[place] = i;
    }

    vector<bool> visited(G.size(), false);
    vector<bool> maintainE(E.size(), false);
    vector<bool> is_p(G.size(), false);
    for(int i = 0; i < ps.size(); i++)
        is_p[ps[i]] = true;
    bfs(G, ps, d, visited, sortE, maintainE, is_p, indexes);
    
    return maintainE;
}

int main(){
    int n, k, d;
    cin >> n >> k >> d;
    graph G(n + 1);
    vector<pair<int,int>> E;
    vector<int> ps(k);
    for(int i = 0; i < k; i++)
        cin >> ps[i];
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
        if(u < v)
            E.emplace_back(u, v);
        else
            E.emplace_back(v, u);
    }
    vector<bool> maintain = solve(E, G, ps, d);
    int count = 0;
    for(int i = 0; i < maintain.size(); i++)
        if(!maintain[i])
            count++;

    cout << count << '\n';
    if(count > 0){
        for(int i = 0; i < maintain.size(); i++){
            if(!maintain[i])
                cout << i + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}