#include<bits/stdc++.h>
using namespace std;

int main(){
    //freopen("output.txt","w",stdout);
    int n,a,b,cas=0;
    while(cin>>n){
        vector<int>adj[25];
        for(int i=1; i<=19; i++){
            if(i>1)cin>>n;
            while(n--){
                cin>>a;
                adj[i].push_back(a);
                adj[a].push_back(i);
            }
        }
        int N;
        cin>>N;
        cout<<"Test Set #"<<++cas<<endl;
        while(N--){
            cin>>a>>b;
            int levels[25]={0};
            queue<int>q;
            levels[a]=0;
            q.push(a);
            int ans=9999;
            while(!q.empty()){
                int top=q.front();
                q.pop();
                for(int i=0; i<adj[top].size(); i++){
                    int child=adj[top][i];
                    if(levels[child]>0 || child==a)continue;
                    levels[child]=levels[top]+1;
                    if(child==b)ans=min(ans,levels[child]);
                    q.push(child);
                }
            }
            cout<<setw(2)<<a<<" to "<<setw(2)<<b<<": "<<ans<<endl;
        }
        cout<<endl;
    }


return 0;
}
