#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int n,r;
    string u,v;
    int scenario=0;
    while(cin>>n>>r){
        if(!n && !r)break;
        int nodes=1;
        map<string,int>encode;
        int graph[205][205];
        memset(graph,INT_MAX,sizeof(graph));
        int c;
        while(r--){
            cin>>u>>v>>c;
            if(encode[u]==0)encode[u]=nodes++;
            if(encode[v]==0)encode[v]=nodes++;
            int x=encode[u];
            int y=encode[v];
            graph[x][y]=c;
            graph[y][x]=c;
        }
        for(int k=1; k<=n; k++){
            for(int i=1; i<=n; i++){
                for(int j=1; j<=n; j++){
                    if(graph[i][j]<min(graph[i][k],graph[k][j])){
                        graph[i][j]=min(graph[i][k],graph[k][j]);
                    }
                }
            }
        }
        cin>>u>>v;
        cout<<"Scenario #"<<++scenario<<endl;
        cout<<graph[encode[u]][encode[v]]<<" tons"<<endl<<endl;

    }
return 0;
}
