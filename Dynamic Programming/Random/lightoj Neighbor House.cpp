#include<bits/stdc++.h>
using namespace std;

struct rgbArr{
    int r,g,b;
}arr[25];

int t,n;
long long dp[25][5];

long long solve(int i=0, int color=3){///red=0, green=1, blue=2
    if(i>=n)return 0;
    long long &ret = dp[i][color];
    if(ret!=-1)return ret;
    long long a=INT_MAX, b=INT_MAX, c=INT_MAX;
    if(color!=0)a = solve(i+1, 0)+arr[i].r;
    if(color!=1)b = solve(i+1, 1)+arr[i].g;
    if(color!=2)c = solve(i+1, 2)+arr[i].b;
    return ret=min(a,min(b,c));
}


int main(){
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        memset(dp,-1,sizeof(dp));
        scanf("%d",&n);
        for(int i=0; i<n; i++)scanf("%d%d%d",&arr[i].r, &arr[i].g, &arr[i].b);
        printf("Case %d: %lld\n",cas,solve());
    }
return 0;
}
