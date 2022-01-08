#include<bits/stdc++.h>
using namespace std;
#define xx first
#define yy second
long long INF = 1;
int main(){
    //freopen("output.txt","w",stdout);
    INF<<=62;
    int t,n,e,q;
    cin>>t;
    while(t--){
        cin>>n>>e;
        pair<long long,long long>g[n+1][n+1];
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                g[i][j].xx=INF;
                g[i][j].yy=INF;
            }
            g[i][i].xx=0;
            g[i][i].yy=0;
        }
        for(int i=0; i<e; i++){
            long long u,v,t,d;
            cin>>u>>v>>t>>d;
            if(g[u][v].xx>t || (g[u][v].xx==t && g[u][v].yy>d)){
                g[u][v].xx=t;
                g[u][v].yy=d;
                g[v][u].xx=t;
                g[v][u].yy=d;
            }
        }
        for(int k=1; k<=n; k++){
            for(int i=1; i<=n; i++){
                for(int j=1; j<=n; j++){
                    if(g[i][k].xx==INF || g[k][j].xx==INF)continue;
                    if(g[i][j].xx>g[i][k].xx+g[k][j].xx ||(g[i][j].xx==g[i][k].xx+g[k][j].xx && g[i][j].yy>g[i][k].yy+g[k][j].yy)){
                        g[i][j].xx=g[i][k].xx+g[k][j].xx;
                        g[i][j].yy=g[i][k].yy+g[k][j].yy;
                    }
                }
            }
        }
        cin>>q;
        int a,b;
        while(q--){
            cin>>a>>b;
            if(g[a][b].xx!=INF)cout<<"Distance and time to reach destination is "<<g[a][b].yy<<" & "<<g[a][b].xx<<"."<<endl;
            else cout<<"No Path."<<endl;
        }
        if(t)cout<<endl;
    }
return 0;
}
