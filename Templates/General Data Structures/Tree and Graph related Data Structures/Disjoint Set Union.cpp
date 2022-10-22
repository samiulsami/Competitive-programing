struct DSU{
    vector<int>parent;
    int n;
    DSU(int n):n(n),parent(n+1){for(int i=0; i<=n; i++)parent[i]=i;}
    inline int Find(int x){
        if(parent[x]==x)return x;
        return parent[x]=Find(parent[x]);
    }
    inline bool Unite(int x, int y){
        x=Find(x);
        y=Find(y);
        if(x!=y){
            parent[x]=y;
            return 1;
        }
        return 0;
    }
};