#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> graph;

graph read_graph(int V, int E){
    vector<vector<int>> G(V + 1);
    for(int i = 0; i < E; i++){
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    return G;
}

vector<int> bfs_comp(graph& G, int s, vector<bool>& visited){
    vector<int> C;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        if(!visited[v])
            C.emplace_back(v);
        visited[v] = true;
        for(int adj: G[v]){
            if(!visited[adj])
                q.push(adj);
        }
    }

    return C;
}

int harmony(graph& G){
    int edges = 0;
    for(int i = 1; i < G.size(); i++){
        bool harmonic = false;
        vector<bool> visited(G.size(), false);
        vector<bool> vb;
        int max = -1;
        while(!harmonic){
            // Pega a componente conectada parcial do no
            vector<int> C = bfs_comp(G, i, visited);
            int C_max = max_element(C.begin(), C.end()) - C.begin();
            if(C[C_max] > max)
                max = C[C_max];
            vb.resize(max + 1, false);
            for(int j = 0; j < C.size(); j++){
                vb[C[j]] = true;
            }
            harmonic = true;
            int missing = -1;
            for(int j = i; j < max; j++){
                if(vb[j] == false){
                    harmonic = false;
                    missing = j;
                    break;
                }
            }
            if(!harmonic){
                G[i].emplace_back(missing);
                G[missing].emplace_back(i);
                edges++;
                i = missing;
            }
            else{
                i = max;
            }
        }

    }
    return edges;
}

int main(){
    int n, m;
    cin >> n >> m;
    graph G = read_graph(n, m);
    cout << harmony(G) << '\n';
    return 0;
}