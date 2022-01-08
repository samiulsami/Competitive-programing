/**
    Edmond-Karp Max flow

    Initialize Capacity to 0
    addEdge(u,v,c) adds a directed edge u-v with capacity=c.
    For undirected edges add another edge v-u.
    maxFlow(S,T) return Maximum Flow from S to T
    Time complexity: O(V * E^2)

*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX=105;
vector<int>graph[MAX];
int capacity[MAX][MAX];
int parent[MAX];
int n;

void addEdge(int u, int v, int cst){
    graph[u].push_back(v);
    capacity[u][v]+=cst;
}

int bfs(int S, int T){
    for(int i=0; i<=n; i++)parent[i]=-1;
    parent[S]=S;
    queue<pair<int,int> >q;
    int u,flow,newFlow;
    q.push({S,INT_MAX});

    while(!q.empty()){
        u=q.front().first;
        flow=q.front().second;
        q.pop();

        for(int v:graph[u]){
            if(parent[v]!=-1 || capacity[u][v]<=0)continue;

            parent[v]=u;
            newFlow=min(flow,capacity[u][v]);
            if(v==T)return newFlow;
            q.push(make_pair(v,newFlow));

        }
    }

    return 0;
}

int maxFlow(int S, int T){
    int flow=0;
    int newFlow=0;
    int cur,prev;

    while(newFlow=bfs(S,T)){
        flow+=newFlow;
        cur=T;
        while(cur!=S){
            prev=parent[cur];
            capacity[prev][cur]-=newFlow;
            capacity[cur][prev]+=newFlow;
            cur=prev;
        }
    }

    return flow;
}

int main(){


return 0;
}
