#include<bits/stdc++.h>
using namespace std;
#define xx first
#define yy second
typedef pair<double,int> pdi;
int main(){
    //freopen("output.txt","w",stdout);
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        double x,y;
        pair<double,double>g[105];
        vector<pdi>graph[105];
        for(int i=0; i<n; i++){
            cin>>x>>y;
            g[i]={x,y};
        }
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                double x1=g[i].xx;
                double y1=g[i].yy;
                double x2=g[j].xx;
                double y2=g[j].yy;
                double dist=sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1)));
                graph[i].push_back({dist,j});
                graph[j].push_back({dist,i});
            }
        }
        priority_queue<pdi,vector<pdi>,greater<pdi> >pq;
        pq.push({0,0});
        double total=0;
        bool vis[105]={0};
        while(!pq.empty()){
            double weight=pq.top().xx;
            int u=pq.top().yy;
            pq.pop();
            if(!vis[u]){
                total+=weight;
                vis[u]=1;
            }
            else continue;
            for(int i=0; i<graph[u].size(); i++){
                if(vis[graph[u][i].yy])continue;
                pq.push(graph[u][i]);
            }
        }
        cout<<fixed<<setprecision(2)<<total<<endl;
        if(t)cout<<endl;
    }
return 0;
}
