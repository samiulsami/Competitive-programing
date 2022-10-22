#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int t,cas=0;
    cin>>t;
    bool first=1;
    cin.ignore();
    cin.ignore();
    while(t--){
        if(first)first=0;
        else if(!first)cout<<endl;
        int nodes[30]={0};
        vector<int>graph[30];
        int cost[30]={0};
        int node_count=0;
        int costIn;
        char nodeIn;
        string s;
        while(getline(cin,s)){
            if(s.empty())break;
            stringstream ss(s);
            string con;
            ss>>nodeIn>>costIn>>con;
            if(nodes[nodeIn-65]==0)nodes[nodeIn-65]=++node_count;
            int tmp=nodes[nodeIn-65];
            cost[tmp]=costIn;
            for(int i=0; i<con.length(); i++){
                if(con[i]>='A' && con[i]<='Z'){
                    if(nodes[con[i]-65]==0)nodes[con[i]-65]=++node_count;
                    int x=nodes[con[i]-65];
                    graph[x].push_back(tmp);
                }
            }
        }
        int dist[30]={0};
        for(int i=1; i<=node_count; i++)dist[i]=cost[i];
        for(int i=1; i<=node_count; i++){
            for(int j=0; j<graph[i].size(); j++){
                dist[graph[i][j]]=max(dist[graph[i][j]],dist[i]+cost[graph[i][j]]);
            }
        }
        cout<<*max_element(dist,dist+node_count+1)<<endl;
    }

return 0;
}
