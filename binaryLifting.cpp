const int ROW = 18;
const int NODES = 200005;
int up[ROW][NODES];

struct Graph {
    int V;
    vector<vector<int>> adj;  

    Graph(int vertices) : V(vertices), adj(vertices + 1) {}

    void addEdge(int u, int v, bool directed = false) {
        adj[u].emplace_back(v);
        if(!directed) adj[v].emplace_back(u);
    }
};

struct BinaryLifting { 
    vector<int> dep;  
    Graph* g;

    BinaryLifting (Graph* graph) : g(graph), dep(graph->V + 1, 0) {
        memset(up, -1, sizeof(up));
    }

    void dfs(int v, int p, int d) { 
        up[0][v] = p; 
        dep[v] = d;
        for(const int& u : g->adj[v]) if(u != p) dfs(u, v, d + 1); 
    }

    void build() {
        dfs(1, -1, 0); // 1 based node indexing
        for(int i = 1; i < ROW; i++) {
            for(int j = 1; j <= g->V; j++) { 
                if(up[i - 1][j] != -1) up[i][j] = up[i - 1][up[i - 1][j]];
            }
        }
    }

    int kthAncestor(int node, int k) {
        if(k > dep[node]) return -1;
        
        for(int i = 0; i < ROW; i++) { 
            if(node != -1) { 
                if(k & (1 << i)) node = up[i][node];
            }
        } 
        return node;
    }

    int lift(int node, int dept) {
        return kthAncestor(node, dept);
    }

    int lca(int a, int b) {
        if(dep[a] < dep[b]) swap(a, b);  
        a = lift(a, dep[a] - dep[b]);
        if(a == b) return a;

        for(int i = ROW-1; i >= 0; i--) {
            if(up[i][a] != up[i][b]) a = up[i][a], b = up[i][b];
        }
        return up[0][a];
    }

    int distance(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a, b)];
    }
};
