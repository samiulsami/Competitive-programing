#include<bits/stdc++.h>
using namespace std;

int dx[5]={1,0,-1,0};
int dy[5]={0,1,0,-1};
inline bool safe(int &a, int &b, int &n, int &m){
    return (a<n && a>=0 && b<m && b>=0);
}

struct edge{
    int a,b,c;
    edge(int a,int b,int c){this->a=a;this->b=b;this->c=c;}
};

class cmp{
    public:
    bool operator()(edge &a, edge &b){
        return a.c>b.c;
    }
};

int main(){
    //freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    for(int cas=1,n,m; cas<=t; cas++){
        cin>>n>>m;
        int maze[n+1][m+1];
        int dist[n+1][m+1];
        memset(dist,-1,sizeof(dist));
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cin>>maze[i][j];
        priority_queue<edge,vector<edge>,cmp>pq;
        pq.push(edge(0,0,maze[0][0]));
        dist[0][0]=maze[0][0];
        while(!pq.empty()){
            edge top=pq.top();
            pq.pop();
            if(dist[top.a][top.b]<top.c)continue;
            for(int i=0; i<4; i++){
                int newa=top.a+dx[i];
                int newb=top.b+dy[i];
                if(!safe(newa,newb,n,m))continue;
                int cost=maze[newa][newb];
                if(dist[top.a][top.b]+cost<dist[newa][newb] || dist[newa][newb]==-1){
                    dist[newa][newb]=dist[top.a][top.b]+cost;
                    pq.push(edge(newa,newb,dist[newa][newb]));
                }
            }
        }
        cout<<dist[n-1][m-1]<<endl;
    }

return 0;
}
