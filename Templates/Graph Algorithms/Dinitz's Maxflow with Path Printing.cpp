struct Dinic{
        struct edge{
            int u,v,cap,flow;
            bool flag=0;
            edge(){}
            edge(int u, int v, int cap):u(u),v(v),cap(cap){
                flow=0;
            }
        };
        vector<edge>edges;
        vector<vector<int> > graph;
        vector<int> lvl,nxt;
        vector<vector<int> >paths;
        int n,edge_cnt,S,T;

        Dinic(int n):n(n),graph(n+10),lvl(n+10),nxt(n+10){
            edge_cnt=0;
        }

        void addEdge(int u, int v, int cap){
            edges.emplace_back(u,v,cap);
            graph[u].push_back(edge_cnt++);
            edges.emplace_back(v,u,0);
            edges.back().flag=1;
            graph[v].push_back(edge_cnt++);
        }

        bool bfs(){
            queue<int>q;
            q.push(S);
            fill(lvl.begin(),lvl.end(),-1);
            lvl[S]=0;
            while(!q.empty()){
                int u=q.front();
                if(u==T)break;
                q.pop();
                for(int edgeID : graph[u]){
                    edge &v = edges[edgeID];
                    if(v.cap<=v.flow || lvl[v.v]!=-1)continue;
                    lvl[v.v]=lvl[u]+1;
                    q.push(v.v);
                }
            }
            return lvl[T]!=-1;
        }

        int dfs(int u, int pathFlow){
            if(pathFlow==0 || u==T)return pathFlow;
            int ret=0;
            int id;
            for(int &edgeID=nxt[u]; edgeID<(int)graph[u].size(); edgeID++){
                id = graph[u][edgeID];
                edge &v = edges[id];
                if(lvl[v.v]!=lvl[u]+1 || v.cap<=v.flow)continue;
                if(ret=dfs(v.v, min(pathFlow, v.cap-v.flow))){
                    edges[id].flow+=ret;
                    edges[id^1].flow-=ret;
                    return ret;
                }
            }
            return 0;
        }

        vector<int>tmp;
        bool vis2[505];

        bool dfs2(int u){
            if(u==n)return 1;
            vis2[u]=1;
            bool ret=0;
            for(int id:graph[u]){
                edge &e = edges[id];
                if((e.cap-e.flow)>0 || e.flag || vis2[e.v])continue;
                if(ret|=dfs2(e.v)){
                    tmp.push_back(e.v);
                    e.flag=1;
                    return 1;
                }
            }
            return ret;
        }

        int maxFlow(int s, int t){
            S=s;
            T=t;
            int flow=0,f=0;
            while(bfs()){
                fill(nxt.begin(),nxt.end(),0);
                while(f=dfs(S,INT_MAX))flow+=f;
            }

            int tmpflow=flow;
            while(tmpflow--){
                tmp.clear();
                memset(vis2,0,sizeof(vis2));
                dfs2(1);
                tmp.push_back(1);
                reverse(all(tmp));
                paths.push_back(tmp);
            }
            return flow;
        }

        void print(){
            for(vi &p:paths){
                pf("%d\n",sz(p));
                for(int i:p)pf("%d ",i);
                nl;
            }
        }

};
