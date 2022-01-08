#include<bits/stdc++.h>
using namespace std;

/*
    lightoj problem : 1108
    verdict: AC
*/

typedef pair<int,int> pii;
#define xx first
#define yy second

bool bellman(vector<pii> *graph, bool *vis, int n){
    vector<int>dist(n,(int)1e8);
    bool cycle=0;
    for(int z=1; z<n; z++){
        for(int i=0; i<n; i++){
            for(auto j: graph[i]){
                if(dist[i]+j.xx<dist[j.yy]){
                    dist[j.yy]=dist[i]+j.xx;
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        if(vis[i])continue;
        for(auto j: graph[i]){
            if(dist[i]+j.xx<dist[j.yy]){
                cycle=1;

                stack<int>dfs;
                dfs.push(i);
                vis[i]=1;
                while(!dfs.empty()){
                    int top=dfs.top();
                    dfs.pop();
                    for(auto k : graph[top]){
                        if(!vis[k.yy]){
                            dfs.push(k.yy);
                            vis[k.yy]=1;
                        }
                    }
                }
            }
        }
    }

    return cycle;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int t,n,m;
    cin>>t;
    for(int cas=1; cas<=t; cas++){

        cin>>n>>m;

        vector<pii>graph[n];
        bool vis[n]={0};

        for(int i=0,u,v,c; i<m; i++){
            cin>>u>>v>>c;
            graph[v].push_back({c,u});
        }

        cout<<"Case "<<cas<<":";
        if(!bellman(graph,vis,n))cout<<" impossible"<<endl;
        else{
            for(int i=0; i<n; i++)if(vis[i])cout<<" "<<i;
            cout<<endl;
        }

    }

return 0;
}
