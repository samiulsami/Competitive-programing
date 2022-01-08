#include<bits/stdc++.h>
using namespace std;

struct edge{
    int u,v,c;
    edge(int u,int v,int c){this->u=u;this->v=v;this->c=c;}
    bool operator<(const edge &e)const{
        if(c!=e.c)return c<e.c;
        if(u!=e.u)return u<e.u;
        return v<e.v;
    }
};
int _find(int r, int *parent){
    return parent[r]=(parent[r]==r?r:_find(parent[r],parent));
}
int main(){
    //freopen("output.txt","w",stdout);
    int t,n;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n;
        vector<edge>edges;
        for(int i=1,c; i<=n; i++){
            for(int j=1; j<=n; j++){
                cin>>c;
                if(j!=n)getchar();
                if(c)edges.push_back(edge(i,j,c));
            }
        }
        int parent[27];
        int counter=0;
        for(int i=1; i<=26; i++)parent[i]=i;
        sort(edges.begin(),edges.end());
        cout<<"Case "<<cas<<":"<<endl;
        for(int i=0,u,v; i<(int)edges.size() && counter<n-1; i++){
            u=_find(edges[i].u,parent);
            v=_find(edges[i].v,parent);
            if(u!=v){
                parent[u]=v;
                cout<<char(edges[i].u+64)<<"-"<<char(edges[i].v+64)<<" "<<edges[i].c<<endl;
                counter++;
            }
        }
    }
return 0;
}
