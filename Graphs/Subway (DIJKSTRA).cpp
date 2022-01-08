#include<bits/stdc++.h>
using namespace std;
typedef pair<double,int> pdi;
typedef pair<int,int>pii;
#define xx first
#define yy second

int main(){
    //freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        vector<pii>edges;
        vector<pdi>graph[205];
        int startx,starty,endx,endy;
        cin>>startx>>starty>>endx>>endy;
        edges.push_back({startx,starty});
        edges.push_back({endx,endy});
        string s;
        cin.ignore();
        while(getline(cin,s)){
            if(s.empty())break;
            stringstream ss(s);
            int x,y;
            int cur_nodes=(int)edges.size();
            while(ss>>x>>y){
                if(x==-1 && y==-1)break;
                edges.push_back({x,y});
            }
            for(int i=cur_nodes; i<(int)edges.size()-1; i++){
                double x1,y1;
                x1=edges[i].xx-edges[i+1].xx;
                y1=edges[i].yy-edges[i+1].yy;
                double cost = sqrt((x1*x1)+(y1*y1));
                graph[i].push_back({cost,i+1});
                graph[i+1].push_back({cost,i});
            }
        }
        for(int i=0; i<(int)edges.size(); i++){
            for(int j=i+1; j<(int)edges.size(); j++){
                double x1,y1;
                x1=edges[i].xx-edges[j].xx;
                y1=edges[i].yy-edges[j].yy;
                double cost = sqrt((x1*x1)+(y1*y1))*4;
                graph[i].push_back({cost,j});
                graph[j].push_back({cost,i});
            }
        }
        priority_queue<pdi,vector<pdi>,greater<pdi> >pq;
        double dist[205];
        dist[0]=0;
        for(int i=0; i<205; i++)dist[i]=-1;
        pq.push({0,0});
        while(!pq.empty()){
            int top=pq.top().yy;
            double cost=pq.top().xx;
            pq.pop();
            if(dist[top]<cost && dist[top]!=-1)continue;
            for(int i=0; i<graph[top].size(); i++){
                int v=graph[top][i].yy;
                double cost=graph[top][i].xx;
                if(dist[v]==-1 || dist[v]>dist[top]+cost){
                    dist[v]=dist[top]+cost;
                    pq.push(make_pair(dist[v],v));
                }
            }
        }
        cout<<round((dist[1]*60)/40000)<<endl;
        if(t)cout<<endl;
    }
return 0;
}
