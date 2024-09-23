struct BFS {
    vector<bool> vis; 
    vector<int> dis; 
    Graph* g;

    BFS(Graph* graph) : g(graph), vis(graph->V + 1, false), dis(graph->V + 1, -1) {}

    void traverse(int s) {
        queue<int> q;
        vis[s] = true;
        dis[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& [to, weight] : g->adj[node]) {
                if (!vis[to]) {
                    vis[to] = true;
                    dis[to] = dis[node] + 1; 
                    q.push(to);
                }
            }
        }
    }
};
