const int K = __lg(N)+2;
struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
	int discoveryTime[N],lvl[N],sparseTable[K][N<<1];
    int n,Time;

    void init(int n, int root=1){
        lvl[root]=0;
        Time=0;
        dfs(root,-1);

        for(int i=1; i<K; i++)
            for(int j=1; j+(1<<i)-1<=Time; j++)
				sparseTable[i][j] = Combine(sparseTable[i-1][j], sparseTable[i-1][j+(1<<(i-1))]);        
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = __lg(v-u+1);
		return Combine(sparseTable[logVal][u], sparseTable[logVal][v-(1<<logVal)+1]);
    }
	
	inline int Combine(const int &a, const int &b){return lvl[a]<lvl[b]?a:b;}
	inline int dist(int u, int v){return lvl[u]+lvl[v] - 2*lvl[lca(u,v)];}
}lca;