struct Dijkstra{

    const int inf = (long long) 1e18;
    vector<int> dis;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    Graph* g;
    
    Dijkstra(Graph* graph) : g(graph), dis(graph->V + 1, inf) {}

    void build(int s){
        reset();
        pq.push({0, s});
        dis[s] = 0;
        while(!pq.empty()){
            auto [cost, nod] = pq.top(); pq.pop(); 
            if(dis[nod] < cost) continue;
            for(auto [to, wt] : g->adj[nod]){
                if(cost + wt < dis[to]){
                    dis[to] = cost + wt;
                    pq.push({dis[to], to});
                }
            }
        }
    }

    void reset(){
        fill(dis.begin(), dis.end(), inf);
    }

};
