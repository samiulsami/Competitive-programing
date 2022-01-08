#include<bits/stdc++.h>
using namespace std;
map<string,int>mp;
map<int,string>s_arr;
class cmp{
public:
    bool operator()(int &a, int &b){
        return mp[s_arr[a]]>mp[s_arr[b]];
    }
};

int main(){
    //freopen("output.txt","w",stdout);
    int n,m,cas=0;
    while(cin>>n){
        mp.clear();
        s_arr.clear();
        string s;
        for(int i=1; i<=n; i++){
            cin>>s;
            mp[s]=i;
            s_arr[i]=s;
        }
        cin>>m;
        string a,b;
        vector<int>graph[n+1];
        int in[n+1]={0};
        for(int i=0,u,v; i<m; i++){
            cin>>a>>b;
            u=mp[a];
            v=mp[b];
            graph[u].push_back(v);
            in[v]++;
        }
        priority_queue<int, vector<int>, cmp>q;
        for(int i=1; i<=n; i++)if(in[i]==0)q.push(i);
        bool first=1;
        cout<<"Case #"<<++cas<<": Dilbert should drink beverages in this order: ";
        while(!q.empty()){
            int top=q.top();
            q.pop();
            if(first)first=0;
            else cout<<" ";
            cout<<s_arr[top];
            for(int i=0; i<graph[top].size(); i++){
                in[graph[top][i]]--;
                if(in[graph[top][i]]==0)q.push(graph[top][i]);
            }
        }
        cout<<".\n"<<endl;
    }

return 0;
}
