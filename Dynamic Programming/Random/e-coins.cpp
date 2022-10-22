#include<bits/stdc++.h>
using namespace std;

struct mval{
    int a,b;
}arr[42];

int dp[42][305][305];
int m,s;

int solve(int i=0, int a=0, int b=0){
    int mod=(a*a)+(b*b);
    if(mod==s)return 0;
    if(i==m || mod>s)return 90001;
    int &ret = dp[i][a][b];
    if(~ret)return ret;
    return ret = min(solve(i+1,a,b),solve(i,a+arr[i].a,b+arr[i].b)+1);
}


int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&m,&s);
        s*=s;
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<m; i++)scanf("%d%d",&arr[i].a,&arr[i].b);
        if(solve()!=90001)printf("%d\n",solve());
        else printf("not possible\n");
    }
return 0;
}

