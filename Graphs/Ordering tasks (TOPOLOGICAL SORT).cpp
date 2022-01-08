#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int n,m;
    while(cin>>n>>m, n||m){
        vector<int> graph[n+1];
        int in[n+1]={0};
        for(int i=0,u,v; i<m; i++){
            cin>>u>>v;
            graph[u].push_back(v);
            in[v]++;
        }
        queue<int>q;
        for(int i=1; i<=n; i++)if(in[i]==0)q.push(i);
        bool first=1;
        while(!q.empty()){
            int top=q.front();
            q.pop();
            if(first)first=0;
            else cout<<" ";
            cout<<top;
            for(int i=0; i<graph[top].size(); i++){
                in[graph[top][i]]--;
                if(in[graph[top][i]]==0)q.push(graph[top][i]);
            }
        }
        cout<<endl;
    }
return 0;
}
