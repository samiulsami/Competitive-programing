#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>pii;

int main(){
    int t,n;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n;
        int u,v,w,edges=0;
        vector<pii>graph[n+1];

        while(cin>>u>>v>>w){
            if(u==0 && v==0 && w==0)break;
            graph[u].push_back({w,v});
            graph[v].push_back({w,u});
            edges++;
        }

        priority_queue<pii,vector<pii>, greater<pii> >pq;
        pq.push({0,0});
        int cost=0;
        bool vis[105]={0};

        while(!pq.empty()){
            pii top=pq.top();
            pq.pop();

            if(!vis[top.second]){
                cost+=top.first;
                vis[top.second]=1;
            }
            else continue;

            for(int i=0,v,w; i<(int)graph[top.second].size(); i++)
                if(!vis[graph[top.second][i].second])pq.push(graph[top.second][i]);
        }

        priority_queue<pii, vector<pii>, less<pii> >pq2;
        memset(vis,0,sizeof(vis));
        pq2.push({0,0});

        while(!pq2.empty()){
            pii top=pq2.top();
            pq2.pop();

            if(!vis[top.second]){
                cost+=top.first;
                vis[top.second]=1;
            }
            else continue;

            for(int i=0; i<(int)graph[top.second].size(); i++)
                if(!vis[graph[top.second][i].second])pq2.push(graph[top.second][i]);
        }

        cout<<"Case "<<cas<<": ";
        if(cost&1)cout<<cost<<"/"<<2<<endl;
        else cout<<cost/2<<endl;
    }
return 0;
}
