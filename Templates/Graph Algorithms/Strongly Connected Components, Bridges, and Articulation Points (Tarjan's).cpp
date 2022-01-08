const int MAX = 100005;

vector<int>graph[MAX];
int discovery_time[MAX],parent[MAX];
int Time=0,scc=0;
stack<int>curTree;
bitset<MAX>inTree;

///Finds strongly connected components
int tarjan_scc(int u){
    int low=discovery_time[u]=++Time;
    curTree.push(u);
    inTree[u]=1;

    for(int v:graph[u])
        if(!discovery_time[v])
            low=min(low,tarjan_scc(v));
        else if(inTree[v])
            low=min(low,discovery_time[v]);

    if(low==discovery_time[u]){
        int top;
        do{
            top=curTree.top();
            curTree.pop();
            inTree[top]=0;
            parent[top]=scc;
        }while(u!=top && !curTree.empty());

        scc++;
    }

    return low;
}

set<pair<int,int> >cutEdges;
bool cutVertex[MAX];

///Finds Bridges and Articulation points
int tarjan(int u, int p){
    int low=discovery_time[u]=++Time;
    int children=0;

    for(int v:graph[u]){
        if(v==p)continue;
        else if(discovery_time[v])
            low=min(low,discovery_time[v]);
        else{
            children++;
            int subtree_min = tarjan(v,u);
            low=min(low,subtree_min);

            if(discovery_time[u]<subtree_min)/// u-v is a cut-edge/bridge
                cutEdges.insert(make_pair(min(u,v),max(u,v)));

            if(discovery_time[u]<=subtree_min){
                /** u is a cut-vertex/articulation point iff:
                    u is not root
                    OR
                    u is root, and has more than 1 children
                */
                if(u!=p)cutVertex[u]=1;
                else if(children>1)cutVertex[u]=1;
            }
        }
    }

    return low;
}
