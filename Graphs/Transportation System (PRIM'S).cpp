#include<bits/stdc++.h>
using namespace std;
typedef pair<double,int> pdi;
#define xx first
#define yy second
int main(){
    //freopen("output.txt","w",stdout);
    int t,n,r;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n>>r;
        pair<double,double> g[n+1];
        double x,y;
        for(int i=0; i<n; i++){
            cin>>x>>y;
            g[i]={x,y};
        }
        vector<pdi>graph[n+1];
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                double x1,x2,y1,y2;
                x1=g[i].xx;
                y1=g[i].yy;
                x2=g[j].xx-x1;
                y2=g[j].yy-y1;
                double dist = sqrt((x2*x2)+(y2*y2));
                graph[i].push_back({dist,j});
                graph[j].push_back({dist,i});
            }
        }
        priority_queue<pdi,vector<pdi>,greater<pdi> >pq;
        pq.push({0,0});
        bool vis[n+1]={0};
        double railroad=0,road=0,states=1;
        while(!pq.empty()){
            double weight = pq.top().xx;
            int u = pq.top().yy;
            pq.pop();
            if(!vis[u]){
                vis[u]=1;
                if(weight>r)railroad+=weight,states++;
                else road+=weight;
            }
            else continue;
            for(int i=0; i<graph[u].size(); i++){
                if(vis[graph[u][i].yy])continue;
                pq.push(graph[u][i]);
            }
        }
        cout<<"Case #"<<cas<<": "<<states<<" "<<(int)round(road)<<" "<<(int)round(railroad)<<endl;
    }
return 0;
}
