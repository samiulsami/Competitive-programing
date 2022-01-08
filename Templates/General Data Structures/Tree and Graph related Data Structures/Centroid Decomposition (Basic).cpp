vector<int>graph[N],centroids[N];
int first=-1;///Root node of centroid tree

namespace CD{
    int parent[N],subtreeSize[N];
    bool vis[N];///Marks centroids
    int n,curSize;

    int dfs(int u, int p);
    int find_centroid(int u, int p);
    void centroid_decomposition(int u, int p);

    void init(int x, int root=1){///Call first
        n=x;
        for(int i=0; i<=n; i++)vis[i]=0;
        centroid_decomposition(root,-1);
    }

    int dfs(int u, int p){
        subtreeSize[u]=1;
        for(int v:graph[u])
            if(!vis[v] && v!=p)subtreeSize[u]+=dfs(v,u);
        return subtreeSize[u];
    }

    int find_centroid(int u, int p){
        for(int v:graph[u])
            if(!vis[v] && v!=p)
                if(subtreeSize[v]>curSize/2)return find_centroid(v,u);
        return u;
    }

    void centroid_decomposition(int u, int p){
        curSize=dfs(u,u);
        int centroid = find_centroid(u,u);
        if(p!=-1){
                centroids[p].push_back(centroid);
                centroids[centroid].push_back(p);
        }
        else first = centroid;
        vis[centroid]=1;
        parent[centroid]=p;
        for(int v:graph[centroid])
            if(!vis[v])centroid_decomposition(v,centroid);
    }
}
