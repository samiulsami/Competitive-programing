#include<bits/stdc++.h>
using namespace std;

char s1[1005],s2[1005];
int dp[1005][1005];

int solve(int i=0, int j=0){
    if(!s1[i] || !s2[j])return 0;
    int &ret = dp[i][j];
    if(ret!=-1)return ret;
    return ret = max((s1[i]==s2[j])+solve(i+1,j+1),max(solve(i+1,j),solve(i,j+1)));
}

int main(){
    while(gets(s1)){
        gets(s2);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",solve());
    }
return 0;
}
