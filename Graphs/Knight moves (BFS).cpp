#include<bits/stdc++.h>
using namespace std;

int dx[]={2,2,-2,-2,1,1,-1,-1};
int dy[]={1,-1,1,-1,2,-2,2,-2};

bool safe(int x, int y){
    return (x>=0 && x<8 && y>=0 && y<8);
}

int bfs(int s1,int s2,int g1,int g2){
    int lvl[9][9]={0};
    queue<pair<int,int> >q;
    q.push(make_pair(s1,s2));
    while(!q.empty()){
        pair<int,int>top=q.front();
        q.pop();
        for(int i=0; i<8; i++){
            int x=top.first+dx[i];
            int y=top.second+dy[i];
            if(!safe(x,y) || lvl[x][y] || (x==s1 && y==s2))continue;
            q.push(make_pair(x,y));
            lvl[x][y]=lvl[top.first][top.second]+1;
        }
    }
    return lvl[g1][g2];
}
int main(){
    //freopen("output.txt","w",stdout);
    string a,b;
    while(cin>>a>>b){
        int s1=a[0]-'a';
        int s2=a[1]-'0'-1;
        int g1=b[0]-'a';
        int g2=b[1]-'0'-1;
        cout<<"To get from "<<a<<" to "<<b<<" takes "<<bfs(s1,s2,g1,g2)<<" knight moves."<<endl;
    }
return 0;
}
