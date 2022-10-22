#include<bits/stdc++.h>
using namespace std;

int dp[1000][1000];

int calc(int x, int y){
    if(x<0 || y<0)return -1;
    if(dp[x][y]!=-1)return dp[x][y];
    int mex=0;
    set<int>se;
    se.insert(calc(x+1,y-2));
    se.insert(calc(x-1,y-2));
    se.insert(calc(x-1,y-3));
    se.insert(calc(x-2,y-1));
    se.insert(calc(x-3,y-1));
    se.insert(calc(x-2,y+1));
    while(se.find(mex)!=se.end())mex++;
    dp[y][x]=mex;
    return dp[x][y]=mex;
}

int main(){
    memset(dp,-1,sizeof(dp));
    int t,n,xorsum,x,y;
    scanf("%d",&t);
    for(int cases=1; cases<=t; cases++){
        scanf("%d",&n);
        xorsum=0;
        while(n--){
            scanf("%d%d",&x,&y);
            xorsum^=calc(x,y);
        }
        printf("Case %d: ",cases);
        if(xorsum)printf("Alice\n");
        else printf("Bob\n");
    }
return 0;
}
