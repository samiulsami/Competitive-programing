#include<bits/stdc++.h>
using namespace std;

int n,m;
double dp[1005][1005];
bool diag[1005][1005]={0};
const double diag_len=141.4213562;
//inline bool safe(int x, int y){return (x>=0 && x<n)&&(y>=0 && y<m);}

int dx[4]={0,1,1};
int dy[4]={1,0,1};

double f(int x, int y){
    if(x==n && y==m)return 0;
    if(x>n || y>m)return 1e8;
    double &ret = dp[x][y];
    if(int(ret)!=-1)return ret;
    ret=1e8;
    for(int i=0; i<3; i++){
        int newx=x+dx[i];
        int newy=y+dy[i];
        double cost;
        if(i==2)cost=diag_len;
        else cost=100;
        if(i==2 && diag[newx][newy]!=1)continue;
        ret=min(ret, f(newx,newy)+cost);
    }
    return ret;
}

int main(){
    for(int i=0; i<1002; i++)for(int j=0; j<1002; j++)dp[i][j]=-1;
    int k;
    cin>>n>>m>>k;
    for(int i=0,x,y; i<k; i++){
        cin>>x>>y;
        diag[x][y]=1;
    }
    cout<<(int)round(f(0,0));
return 0;
}
