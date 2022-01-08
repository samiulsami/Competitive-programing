#include<bits/stdc++.h>
using namespace std;

int n;
int first[1005];
int second[1005];
int dp[1005][1005][3];
int dir[1005][1005][3];

bool solve(int i=0, int j=0, int stat=1){
    if(i==n && j==n)return 1;
    if(i>n || j>n)return 0;
    int &ret = dp[i][j][stat];
    if(ret!=-1)return ret;
    ret=0;
    int &direct = dir[i][j][stat];
    if(stat==0){///reds>blacks (0=red,1=black)
        if(first[i]==0 && second[j]==0)return ret;
        if(first[i]==1)ret|=solve(i+1,j,1);
        if(ret)direct=1;
        if(second[j]==1)ret|=solve(i,j+1,1);
        if(ret && direct==-1)direct=2;
    }
    else if(stat==1){///reds==blacks
        if(first[i]==0)stat=0;
        else stat=2;
        ret|=solve(i+1,j,stat);
        if(ret)direct=1;

        if(second[j]==0)stat=0;
        else stat=2;
        ret|=solve(i,j+1,stat);
        if(ret && direct==-1)direct=2;
    }
    else if(stat==2){///reds<blacks
        if(first[i]==1 && second[j]==1)return ret;
        if(first[i]==0)ret|=solve(i+1,j,1);
        if(ret)direct=1;
        if(second[j]==0)ret|=solve(i,j+1,1);
        if(ret && direct==-1)direct=2;
    }
    return ret;
}

int main(){
    cin>>n;
    char c;
    memset(dp,-1,sizeof(dp));
    memset(dir,-1,sizeof(dir));
    for(int i=0; i<n; i++){
        cin>>c;
        if(c=='1')first[i]=1;
        else first[i]=0;
    }
    for(int i=0; i<n; i++){
        cin>>c;
        if(c=='1')second[i]=1;
        else second[i]=0;
    }
    bool possible = solve();
    if(possible){
        int i=0,j=0,stat=1;
        while(dir[i][j][stat]!=-1 && i<=n && j<=n){
            int &direct=dir[i][j][stat];
            if(direct==1)i++,cout<<1;
            else j++,cout<<2;
            if(stat==1){
                if(direct==1){
                    if(first[i-1]==0)stat=0;
                    else stat=2;
                }
                else{
                    if(second[j-1]==0)stat=0;
                    else stat=2;
                }
            }
            else stat=1;
        }
    }
    else cout<<"Impossible";
return 0;
}
