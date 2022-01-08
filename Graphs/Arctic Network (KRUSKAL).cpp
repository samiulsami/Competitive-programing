#include<bits/stdc++.h>
using namespace std;

struct edge{
    int u,v;
    double c;
    bool operator<(const edge &e)const{
        return c<e.c;
    }
    edge(int u,int v,double c){this->u=u;this->v=v;this->c=c;}
};

int _find(int r,int parent[]){
    return parent[r]=(parent[r]==r?r:_find(parent[r],parent));
}

int main(){
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    int t,s,p;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&s,&p);
        int parent[p+1];
        vector<edge> edges;
        pair<double,double>coordinates[p+1];
        for(int i=0; i<p; i++){
            double u,v;
            scanf("%lf%lf",&u,&v);
            coordinates[i]={u,v};
        }
        for(int i=0; i<p; i++){
            for(int j=i+1; j<p; j++){
                double x1=coordinates[j].first-coordinates[i].first;
                double y1=coordinates[j].second-coordinates[i].second;
                double dist=sqrt((x1*x1)+(y1*y1));
                edges.push_back(edge(i,j,dist));
            }
        }
        sort(edges.begin(),edges.end());
        for(int i=0; i<p; i++)parent[i]=i;
        int counter=0;
        double cost=0;
        for(int i=0,u,v; i<edges.size() && counter<p-s; i++){
            u=_find(edges[i].u,parent);
            v=_find(edges[i].v,parent);
            if(u!=v){
                parent[u]=v;
                counter++;
                cost=max(cost,edges[i].c);
            }
        }
        printf("%0.2f\n",cost);
    }
return 0;
}
