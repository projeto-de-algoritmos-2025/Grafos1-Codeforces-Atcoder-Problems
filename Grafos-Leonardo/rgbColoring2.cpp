#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> graph;
typedef enum color {W, R, G, B} color;

bool can_color(graph& Gr, vector<color> Cs, int v, color c){
    for(int adj: Gr[v])
        if(Cs[adj] == c)
            return false;
    return true;
}

size_t rgb_color(graph& Gr, int v, vector<color> Cs, vector<int> component){    
    if(v == component.size())
        return 1;
    size_t total = 0;
    for(color c: {R, G, B}){
        if(can_color(Gr, Cs, component[v], c)){
            Cs[component[v]] = c;
            total += rgb_color(Gr, v + 1, Cs, component);
            Cs[component[v]] = W;
        }
    }
    return total;
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

vector<vector<int>> get_components(graph& G){
    vector<bool> visited(G.size(), false);
    vector<vector<int>> Cs;
    for(int v = 0; v < G.size(); v++){
        if(!visited[v]){
            vector<int> C = bfs_comp(G, v, visited);
            Cs.emplace_back(C);
        }
    }

    return Cs;

}

size_t solve(graph& Gr){
    vector<vector<int>> components = get_components(Gr);
    size_t total = 1;
    for(vector<int> c: components){
        if(c[0] == 0) continue;
        vector<color> Cs(Gr.size(), W);
        total *= rgb_color(Gr, 0, Cs, c);
    }
    return total;
}


int main(){
    int n, m;
    cin >> n >> m;
    graph Gr(n + 1);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        Gr[u].emplace_back(v);
        Gr[v].emplace_back(u);
    }
    vector<color> Cs(n + 1, W);
    cout << solve(Gr) << '\n';
    return 0;
}