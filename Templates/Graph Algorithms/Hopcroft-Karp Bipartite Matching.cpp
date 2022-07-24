/**
    Hopcroft-Karp Bipartite Matching.
    Based on:
    http://zobayer.blogspot.com/2010/05/maximum-matching.html
    https://en.wikipedia.org/wiki/Hopcroft-Karp_algorithm

    Number of nodes in set U = n (numbered 0 to n-1)
    Number of nodes in set V = m (numbered n to n+m-1)

    Create a HopcroftKarp object with total number of nodes = (|U| + |V|)
    addEdge(x,y) adds a directed edge x-y
    bpm() returns maximum matching between set U and V
    Time complexity: O(sqrt(V)*E)
**/
struct HopcroftKarp{

    vector<vector<int> >graph;
    vector<int>matchL,matchR;
    vector<int>dist;
    int n;

    HopcroftKarp(int n):n(n),graph(n),matchL(n),matchR(n),dist(n){}

    void addEdge(int u, int v){
        graph[u].push_back(v);
    }

    bool bfs(){
        queue<int>q;
        for(int i=0; i<n; i++){
            if(matchL[i]==-1){
                dist[i]=0;
                q.push(i);
            }
            else dist[i]=-1;
        }
        bool flag=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v:graph[u]){
                if(matchR[v]==-1)flag=1;
                else if(dist[matchR[v]] == -1){
                    dist[matchR[v]] = dist[u]+1;
                    q.push(matchR[v]);
                }
            }
        }
        return flag;
    }

    bool dfs(int u){
        for(int v:graph[u]){
            if(matchR[v]==-1 || (dist[matchR[v]] == dist[u]+1 && dfs(matchR[v]))){
                matchR[v]=u;
                matchL[u]=v;
                return true;
            }
        }
        dist[u]=-1;
        return false;
    }

    int bpm(){
        int matching=0;
        for(int i=0; i<n; i++)matchL[i]=matchR[i]=-1;
        while(bfs()){
            for(int i=0; i<n; i++){
                if(matchL[i]==-1 && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
};
