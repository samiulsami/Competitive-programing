#include<bits/stdc++.h>
using namespace std;

/*
    LightOJ: 1417 - Forwarding Emails
    verdict: AC
*/

const int MAX = 50005;

vector<int>graph[MAX];
int parent[MAX];
int discovery_time[MAX];
int Time;
int scc;
stack<int>curPath;
bitset<MAX>inPath;

int counter[MAX];
int dp[MAX];
int n;

int tarjan_scc(int u){
    discovery_time[u]=++Time;

    int low=discovery_time[u];
    curPath.push(u);
    inPath[u]=1;

    for(int v:graph[u])
        if(!discovery_time[v])
            low=min(low,tarjan_scc(v));
        else if(inPath[v])
            low=min(low,discovery_time[v]);


    if(low==discovery_time[u]){
        int top;

        do{
            top=curPath.top();
            curPath.pop();
            parent[top]=scc;
            inPath[top]=0;

        } while(top!=u && !curPath.empty());

        scc++;
    }

    return low;
}

int solve(int u){
    int &ret=dp[u];
    if(ret!=-1)return ret;

    int root=parent[u];
    ret=counter[root];

    for(int v:graph[u]){
        if(parent[v]!=root)ret=max(ret,counter[root]+solve(v));
        else ret=max(ret,solve(v));
    }

    return ret;
}

int main(){
    int t;
    scanf("%d",&t);

    for(int cas=1; cas<=t; cas++){
        scanf("%d",&n);

        for(int i=0; i<=n; i++){
            graph[i].clear();
            parent[i]=i;
            discovery_time[i]=0;
            counter[i]=0;
            dp[i]=-1;
        }
        scc=0;
        Time=0;

        for(int i=0,u,v; i<n; i++){
            scanf("%d%d",&u,&v);
            graph[u].push_back(v);
        }

        inPath.reset();
        for(int i=1; i<=n; i++)
            if(!discovery_time[i])
                tarjan_scc(i);

        for(int i=1; i<=n; i++)
            counter[parent[i]]++;

        int maxNodes=-1;
        int startingNode=-1;

        for(int i=1; i<=n; i++){
            //cout<<parent[i]<<": "<<i<<"-"<<counter[parent[i]]<<endl;
            int val=solve(i);

            if(val>maxNodes){
                maxNodes=val;
                startingNode=i;
            }
        }

        printf("Case %d: %d\n",cas,startingNode);
    }

return 0;
}
