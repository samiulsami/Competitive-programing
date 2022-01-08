#include<bits/stdc++.h>
using namespace std;

/*
    lightoj problem: 1002
    verdict: AC
*/
typedef pair<int,int> pii;
#define sf(x) scanf("%d",&x);

struct cmp{

    bool operator()(pii &a, pii &b){
        return a.first>b.first;
    }

};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t,n,m,goal;
    sf(t);
    for(int cas=1; cas<=t; cas++){
        scanf("%d%d",&n,&m);
        vector<pair<int,int> >graph[n+1];
        for(int i=0,u,v,w; i<m; i++){
            scanf("%d%d%d",&u,&v,&w);
            graph[u].push_back(make_pair(w,v));
            graph[v].push_back(make_pair(w,u));
        }
        sf(goal);

        int dist[505];
        memset(dist, -1, sizeof(dist));
        dist[goal]=0;

        priority_queue<pii, vector<pii>, cmp >pq;
        pq.push(make_pair(0,goal));
        while(!pq.empty()){
            pii top=pq.top();
            pq.pop();
            int u,v,w;
            u=top.second;
            for(int i=0; i<(int)graph[u].size(); i++){
                v=graph[u][i].second;
                w=graph[u][i].first;
                if(dist[v]==-1 || dist[v]>max(dist[u],w)){
                    dist[v]=max(dist[u],w);
                    pq.push(graph[u][i]);
                }
            }
        }
        printf("Case %d:\n",cas);
        for(int i=0; i<n; i++){
            if(dist[i]!=-1)printf("%d\n",dist[i]);
            else printf("Impossible\n");
        }

    }

return 0;
}
