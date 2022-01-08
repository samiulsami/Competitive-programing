#include<bits/stdc++.h>
using namespace std;

struct edge{
    int u,v,c;
    edge(int u,int v,int c):u(u),v(v),c(c){}
    bool operator<(const edge &e)const{return c<e.c;}
};

int _find(int r, int *parent){
    return parent[r]=parent[r]==r?r:_find(parent[r],parent);
}

int main(){
    int n,m;
    cin>>n>>m;
    int parent[n+1];
    for(int i=0; i<=n; i++)parent[i]=i;
    vector<edge>edges;
    for(int i=0,u,v,c; i<m; i++){
        cin>>u>>v>>c;
        edges.push_back(edge(u,v,c));
    }
    sort(edges.begin(),edges.end());
    int cost=0;
    int counter=0;
    for(int i=0; i<n && counter<n-1; i++){
        if(_find(edges[i].u,parent)!=_find(edges[i].v,parent)){
            parent[_find(edges[i].u,parent)]=parent[_find(edges[i].v,parent)];
            cost+=edges[i].c;
            counter++;
        }
    }
    cout<<cost;
return 0;
}
