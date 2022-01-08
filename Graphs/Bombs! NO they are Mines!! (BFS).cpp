#include<bits/stdc++.h>
using namespace std;

int graph[1005][1005];
int rr,cc;

int dx[5]={0,1,0,-1};
int dy[5]={1,0,-1,0};

int bfs(int goalr,int goalc,int startr,int startc){
    queue<pair<int,int> >q;
    q.push(make_pair(startr,startc));
    int vis[1005][1005]={0};
    vis[startr][startc]=0;
    while(!q.empty()){
        pair<int,int>top=q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int newr=top.first+dx[i];
            int newc=top.second+dy[i];
            if(graph[newr][newc] || newr>=rr || newc>=cc || newr<0 || newc<0 || vis[newr][newc] || (newc==startc && newr==startr))continue;
            vis[newr][newc]=vis[top.first][top.second]+1;
            q.push(make_pair(newr,newc));
        }
    }
    return vis[goalr][goalc];
}

int main(){
    //freopen("output.txt","w",stdout);
    int q;
    while(cin>>rr>>cc){
        if(!cc && !rr)break;
        cin>>q;
        memset(graph,0,sizeof(graph));
        int row,colnum,col;
        while(q--){
            cin>>row>>colnum;
            while(colnum--){
                cin>>col;
                graph[row][col]=1;
            }
        }
        int startr,startc,goalr,goalc;
        cin>>startr>>startc>>goalr>>goalc;
        cout<<bfs(goalr,goalc,startr,startc)<<endl;
    }

return 0;
}
