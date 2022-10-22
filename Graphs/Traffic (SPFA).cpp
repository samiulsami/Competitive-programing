#include<bits/stdc++.h>
using namespace std;

/*
    uva 10449
    verdict: AC
*/

typedef pair<int,int> pii;
#define xx first
#define yy second
const int inf = 1e8;

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int n,cases=0;
    while(cin>>n){
        vector<pii>graph[n+1];
        int costs[n+1];
        for(int i=1; i<=n; i++)cin>>costs[i];
        int r;
        cin>>r;
        for(int i=0,u,v; i<r; i++){
            cin>>u>>v;
            int cst=costs[v]-costs[u];
            cst=cst*cst*cst;
            graph[u].push_back(pii(cst,v));
        }

        int dist[n+1];
        for(int i=0; i<=n; i++)dist[i]=inf;
        dist[1]=0;

        queue<int>q;
        bool inqueue[n+1]={0};
        int cnt[n+1]={0};
        inqueue[1]=1;
        if(n>0)q.push(1);
        bool ncycle=0;
        while(!q.empty() && !ncycle){
            int top=q.front();
            q.pop();
            inqueue[top]=0;
            for(auto j:graph[top]){
                if(dist[top]+j.xx<dist[j.yy]){
                    dist[j.yy]=dist[top]+j.xx;
                    if(!inqueue[j.yy]){
                        inqueue[j.yy]=1;
                        q.push(j.yy);
                        if(++cnt[j.yy]>n)ncycle=1;
                    }
                }
            }
        }

        for(int z=0; z<2; z++){
            for(int i=1; i<=n; i++){
                for(auto j:graph[i]){
                    if(dist[i]+j.xx<dist[j.yy]){
                            dist[j.yy]=-inf;
                        }
                    }
                }
        }

        int queries;
        cout<<"Set #"<<++cases<<endl;
        cin>>queries;
        while(queries--){
            int x;
            cin>>x;
            if(dist[x]<3 || dist[x]==inf)cout<<"?"<<endl;
            else cout<<dist[x]<<endl;
        }

    }

return 0;
}
