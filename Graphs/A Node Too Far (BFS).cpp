#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int n,a,b,ans,ttl,root;
    for(int cas=0;;){
        cin>>n;
        if(!n)break;
        map<int,vector<int> >adj;
        int total=0;
        for(int i=0,a,b; i<n; i++){
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int start,ttl;
        while(cin>>start>>ttl){
            if(!start && !ttl)break;
            int ans=0;
            map<int,int>level;
            level[start]=0;
            queue<int>q;
            q.push(start);
            while(!q.empty()){
                int top=q.front();
                q.pop();
                for(int i=0; i<adj[top].size(); i++){
                    int child=adj[top][i];
                    if(level.count(child))continue;
                    q.push(child);
                    level[child]=level[top]+1;
                }
            }
            ans+=adj.size()-level.size();
            for(map<int,int>::const_iterator it=level.begin(); it!=level.end(); it++)if((*it).second>ttl)ans++;
            cout<<"Case "<<++cas<<": "<<ans<<" nodes not reachable from node "<<start<<" with TTL = "<<ttl<<"."<<endl;
        }
    }
return 0;
}
