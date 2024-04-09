/**
    Minimum cost Maximum flow with SPFA

    To initialize, call mcmf<int,int> myFlow(n) where n is the number of nodes
    myFlow.addEdge(u,v,cap,cst) adds a directed edge u-v with capacity=cap and cost=cst.
    For undirected edges add another edge v-u.
    myFlow.MincostMaxflow(source, sink) returns Minimum cost Maximum Flow pair(flow, cost) from S to T

    For Maximum cost Maximum Flow multiply the costs by '-1' before adding edges

    Time Complexity: ????!!
*/

/// U = cap type, T = cost type
template<typename U, typename T> struct mcmf{
        struct edge{
            int u,v;
            U cap, flow;
            T cost;
            edge(){}
            edge(int u, int v, U cap, T cost):u(u),v(v),cap(cap),cost(cost){
                flow=0;
            }
        };

        vector<edge>edges;
        vector<vector<int>>graph;
        vector<int>parent;
        vector<T>dist;
        vector<bool>inQueue;
        int edge_cnt;
        queue<int>q;
        int n;
        T INF_COST;
        U INF_FLOW;

        template <typename X>
        X MaxValue() {
          return std::numeric_limits<X>::max();
        }

        mcmf(int nn):graph(nn+1), parent(nn+1), dist(nn+1), inQueue(nn+1){
            edge_cnt = 0;
            n = nn;
            INF_COST = MaxValue<T>();
            INF_FLOW = MaxValue<U>();
        }

        void addEdge(int u, int v, U cap, T cost){
            edges.emplace_back(u,v,cap,cost);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0,-cost);
            graph[v].push_back(edge_cnt++);
        }

        bool spfa(int source, int sink){
            for(int i=0; i<n; i++){
                    parent[i]=-1;
                    dist[i]=INF_COST;
                    inQueue[i]=0;
            }

            dist[source]=0;
            q.push(source);

            while(!q.empty()){
                int u = q.front();
                T cost = dist[u];
                inQueue[u]=0;
                q.pop();

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    if(cost+v.cost<dist[v.v]){
                        dist[v.v]=cost+v.cost;
                        parent[v.v]=id;
                        if(!inQueue[v.v]){
                                q.push(v.v);
                                inQueue[v.v]=1;
                        }
                    }
                }
            }

            return (dist[sink]!=INF_COST);
        }

        bool dijkstra(int source, int sink){
            for(int i=0; i<n; i++){
                    parent[i]=-1;
                    dist[i]=INF_COST;
            }

            priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > >pq;
            dist[source]=0;
            pq.push({0,source});

            while(!pq.empty()){
                int u = pq.top().second;
                T cost = pq.top().first;
                pq.pop();
                if(dist[u]<cost)continue;

                for(int id:graph[u]){
                    edge &v = edges[id];
                    if(v.cap<=v.flow)continue;
                    if(cost + v.cost<dist[v.v]){
                        dist[v.v]=cost + v.cost;
                        parent[v.v]=id;
                        pq.push({dist[v.v],v.v});
                    }
                }
            }

            return (dist[sink]!=INF_COST);
        }

        pair<U, T> MincostMaxflow(int source, int sink){
            if(source == sink)return {0,0};

            U flow=0;
            T cost=0;

            while(spfa(source, sink)){
                U min_flow = INF_FLOW;
                int cur,id;

                cur=sink;
                do{
                    id=parent[cur];
                    edge &edgeID = edges[id];
                    min_flow=min(min_flow,(U)(edgeID.cap-edgeID.flow));
                    cur = edgeID.u;
                }while(cur!=source);

                cur=sink;
                do{
                    id=parent[cur];
                    edges[id].flow+=min_flow;
                    edges[id^1].flow-=min_flow;
                    cur=edges[id].u;
                }while(cur!=source);

                flow+=min_flow;
                cost+=dist[sink]*min_flow;///If cost is for 1 unit of flow
            }

            return {flow, cost};
        }
};