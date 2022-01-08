#include<bits/stdc++.h>
using namespace std;

int r,c,n;
int grid[11][101];
int dp[11][101];
int vis[11][101]={0};
int anext[11][101];
int mx=(1<<30)+1;
int color=1;

int solve(int i, int j){
    if(j==c-1)return grid[i][j];
    int &ret=dp[i][j];

    if(vis[i][j]==color)return ret;
    vis[i][j]=color;
    ret=mx;

    for(int k=-1; k<=1; k++){

        int newi=(i+k);

        if(newi<0)newi=r-1;
        else newi%=r;

        int val=solve(newi,j+1)+grid[i][j];
        if(ret>val){
            ret=val;
            anext[i][j]=newi;
        }
        else if(ret==val){
            anext[i][j]=min(anext[i][j],newi);
        }
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);

    while(scanf("%d%d",&r,&c)!=EOF){

        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                anext[i][j]=-1;
                scanf("%d",&grid[i][j]);
            }
        }

        color++;

        int ans=INT_MAX;
        int start=-1;

        for(int i=0; i<r; i++){
            if(ans>solve(i,0)){
                ans=solve(i,0);
                start=i;
            }
        }

        int i=start,j=0;

        printf("%d",start+1);
        while(anext[i][j]!=-1){

            int nxt=anext[i][j];

            i=nxt;
            j++;

            printf(" %d",nxt+1);

        }
        printf("\n%d\n",ans);
    }
return 0;
}
