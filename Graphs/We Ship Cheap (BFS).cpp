#include<bits/stdc++.h>
using namespace std;
map<string,vector<string> >graph;
map<string,string>tree;

void printpath(string source){
    if(tree[source]==source)return;
    printpath(tree[source]);
    cout<<tree[source]<<" "<<source<<endl;
}

void bfs(string source, string goal){
    tree[source]=source;
    map<string,int>vis;
    vis[source]=1;
    queue<string>q;
    q.push(source);
    while(!q.empty()){
        string top=q.front();
        if(top==goal){
                printpath(top);
                return;
        }
        q.pop();
        for(int i=0; i<graph[top].size(); i++){
            if(vis[graph[top][i]]==1)continue;
            tree[graph[top][i]]=top;
            vis[graph[top][i]]=1;
            q.push(graph[top][i]);
        }
    }
    cout<<"No route"<<endl;
}

int main(){
    //freopen("output.txt","w",stdout);
    string a,b;
    int n;
    bool first=0;
    while(cin>>n){
        if(first)cout<<endl;
        first=1;
        graph.clear();
        tree.clear();
        while(n--){
            cin>>a>>b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        string source,goal;
        cin>>source>>goal;
        bfs(source,goal);
    }
return 0;
}
