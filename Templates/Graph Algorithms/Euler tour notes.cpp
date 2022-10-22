/**Query path from u to v (Mo's algorithm usually)
if(dTime[u]>dTime[v])swap(u,v)
If u==LCA(u,v), then l=dTime[u] and r=dTime[v].
Otherwise, l=eTime[u] and r=dTime[v]. For Mo's algorithm, handle LCA(u,v) specially since it does not appear within range[l,r] in this case.
Ignore elements that appear twice within this range, as appearing twice means that we've left their subtree.
*/
void dfs(int u, int p){
        dTime[u]=++Time;
        euler[Time]=u;
        for(int v:graph[u]){
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
            }
        }
        eTime[u]=++Time;
        euler[Time]=u;
}
///---------------------------------------------------------
/**Query the subtree of node u.
if(dTime[u]>dTime[v])swap(u,v)
l=dTime[u] and r=eTime[u]
*/

void dfs(int u, int p){
    dTime[u]=++Time;
    for(int v:graph[u])
        if(v!=p)dfs(v,u);
    eTime[u]=Time;
}

