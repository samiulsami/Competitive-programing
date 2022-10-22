#include<bits/stdc++.h>
using namespace std;

int to_char[30];
int to_int[130];
int in[30];
vector<int>nodes,graph[21];

void dfs(vector<int> &x, int *vis){
    bool allvis=1;
    priority_queue<int,vector<int>, greater<int> >pq;
    for(int i=0; i<(int)nodes.size(); i++)
            if(in[to_int[nodes[i]]]==0 && !vis[to_int[nodes[i]]])
                pq.push(nodes[i]),allvis=0;

    while(!pq.empty()){
        int top=to_int[pq.top()];
        pq.pop();
        vis[top]=1;
        for(int i=0; i<graph[top].size(); i++)in[graph[top][i]]--;
        x.push_back(top);
        dfs(x,vis);
        x.pop_back();
        vis[top]=0;
        for(int i=0; i<graph[top].size(); i++)in[graph[top][i]]++;
    }

    if(!allvis)return;
    for(int i=0; i<(int)x.size(); i++){
        cout<<(char)to_char[x[i]];
    }
    cout<<endl;
}

int main(){
    //freopen("output.txt","w",stdout);
    string s;
    bool first=1;
    while(getline(cin,s)){
        if(first)first=0;
        else cout<<endl;
        nodes.clear();
        for(int i=0; i<21; i++)graph[i].clear();
        memset(in,0,sizeof(in));
        for(int i=0; i<s.length(); i++){
            if(s[i]==' ')continue;
            nodes.push_back(s[i]);
            to_char[(int)nodes.size()-1]=s[i];
            to_int[s[i]]=(int)nodes.size()-1;
        }
        getline(cin,s);
        for(int i=0,u,v; i<s.length(); i++){
            u=to_int[s[i]];
            v=to_int[s[i+2]];
            graph[u].push_back(v);
            in[v]++;
            i+=3;
        }
        vector<int>x;
        int vis[21]={0};
        dfs(x,vis);
    }
return 0;
}
