struct DFS {    
    vector<int> color;
    Graph* g;

    DFS(Graph* graph) : g(graph), color(graph->V + 1, 0) {}

    bool traverse(int s, int c) { 
        color[s] = c;
        for(auto x : g->adj[s]) {
            if(!color[x]) { // p[c] ekhane next adjacent color bujhay, change korba
                if(!traverse(x, p[c])) return false;
            }
            if(color[s] == color[x]) return false;
        }
        return true;
    }
};
