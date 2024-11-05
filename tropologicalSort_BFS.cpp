vector<int> tSort(Graph& g) {
    int n = g.V;
    vector<int> inDeg(n);
    
    for(int i = 0; i < n; i++) {
        for(auto [v, w] : g.adj[i]) {
            inDeg[v]++;
        }
    }
    
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(!inDeg[i]) q.push(i);
    }
    
    vector<int> topo;
    while(!q.empty()) {
        int v = q.front();
        topo.push_back(v);
        q.pop();
        
        for(auto [u, w] : g.adj[v]) {
            inDeg[u]--;
            if(!inDeg[u]) q.push(u);
        }
    }
    
    return topo.size() == n ? topo : vector<int>();
}
