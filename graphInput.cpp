struct Graph {
    int V;
    vector<vector<pair<int, int>>> adj;  

    Graph(int vertices) : V(vertices), adj(vertices + 1) {}

    void addEdge(int u, int v, int w = 1, bool directed = false) {
        adj[u].emplace_back(v, w);
        if (!directed) adj[v].emplace_back(u, w);
    }

    void clear() {
        for (auto& edges : adj) {
            edges.clear();
        }
    }

};
