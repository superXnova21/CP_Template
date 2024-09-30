class DisjointSet{
    vector<int> size, parent;
public:
    DisjointSet(int n){
        size.assign(n+1, 1);
        parent.resize(n+1);
        for(int i = 0; i <= n; i++) parent[i] = i;
    }
    int findParent(int u){
        if(u == parent[u])
            return u;
        return parent[u] = findParent(parent[u]);
    }

    bool isSameSet(int u, int v) { return findParent(u) == findParent(v); }
    
    void unionBySize(int u, int v){
        int ultp_u = findParent(u);
        int ultp_v = findParent(v);
        if(ultp_u != ultp_v){
            if(size[ultp_u] < size[ultp_v])
                swap(ultp_u, ultp_v);
            parent[ultp_v] = ultp_u;
            size[ultp_u] += size[ultp_v];
        }
        return;
    }
};
