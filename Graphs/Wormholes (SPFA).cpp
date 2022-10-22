#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>pii;

bool spfa(vector<pii> *graph, int n){
    vector<int>dist(n,(int)1e8);
    bool inqueue[n]={0};
    int cnt[n]={0};
    stack<int>q;
    q.push(0);
    inqueue[0]=1;
    dist[0]=0;
    while(!q.empty()){
        int top=q.top();
        q.pop();
        inqueue[top]=0;
        for(int i=0,u,c; i<(int)graph[top].size(); i++){
            u=graph[top][i].second;
            c=graph[top][i].first;
            if(dist[top]+c<dist[u]){
                dist[u]=dist[top]+c;
                if(!inqueue[u]){
                    q.push(u);
                    inqueue[u]=1;
                    if(++cnt[u]>n)return 1; ///Negative cycle found
                }
            }
        }
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);
        vector<pii>graph[n];
        for(int u,v,c,i=0; i<m; i++){
            scanf("%d%d%d",&u,&v,&c);
            graph[u].push_back({c,v});
        }
        if(spfa(graph,n))printf("possible\n");
        else printf("not possible\n");
    }
return 0;
}
