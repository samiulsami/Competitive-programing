bool spfa(int source,int n){
    bitset<105>inQueue;
    int relaxCount[n+5];
    ll dist2[n+5];
    for(int i=0; i<=n+1; i++){
        dist2[i]=INT_MAX;
        relaxCount[i]=0;
    }
    dist2[source]=0;
    queue<int>q;
    q.push(source);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        inQueue[u]=0;
        for(pii edge:graph[u]){
            int v = edge.yy;
            int cst=edge.xx;
            if(dist2[v]>dist2[u]+cst){
                dist2[v]=dist2[u]+cst;
                if(++relaxCount[v]>n)return 1;
                else if(!inQueue[v]){
                    inQueue[v]=1;
                    q.push(v);
                }
            }
        }
    }
    return 0;
}
