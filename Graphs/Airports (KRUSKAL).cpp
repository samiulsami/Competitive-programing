#include<bits/stdc++.h>
using namespace std;
struct edge{
    int u,v,c;
    bool operator<(const edge &e)const{return c<e.c;}
    edge(int u,int v,int c){this->u=u;this->v=v;this->c=c;}
};
int _find(int r,int *parent){
    return parent[r]=(parent[r]==r?r:_find(parent[r],parent));
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t,n,m,a;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n>>m>>a;
        vector<edge>edges;
        int parent[n+2];
        for(int i=0,u,v,c; i<m; i++){
            cin>>u>>v>>c;
            edges.push_back(edge(u,v,c));
        }
        sort(edges.begin(),edges.end());
        for(int i=1; i<=n; i++)parent[i]=i;
        long long counter=0,cost=a,airports=1;
        for(int i=0,u,v,c; i<m && counter<n-1; i++){
            u=_find(edges[i].u,parent);
            v=_find(edges[i].v,parent);
            c=edges[i].c;
            if(u!=v){
                parent[u]=v;
                counter++;
                if(a<=c)cost+=a,airports++;
                else cost+=c;
            }
        }
        int base=_find(1,parent);
        if((int)edges.size()>0)base=_find(edges[0].u,parent);
        for(int i=1,u; i<=n; i++){
            u=_find(i,parent);
            if(u!=base){
                parent[u]=base;
                cost+=a;
                airports++;
            }
        }
        cout<<"Case #"<<cas<<": "<<cost<<" "<<airports<<endl;
    }
return 0;
}
