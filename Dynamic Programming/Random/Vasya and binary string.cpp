#include<bits/stdc++.h>
using namespace std;

int n;
long long dp[102][102][102];
char s[102];
int arr[102];

long long solve(int l=0, int r=n, int counter=1){
    if(l==r)return 0;
    long long &ret = dp[l][r][counter];
    if(ret!=-1)return ret;
    ret = arr[counter]+solve(l+1,r,1);
    for(int i=l+1; i<r; i++)
        if(s[l]==s[i])
            ret = max(ret, solve(l+1,i,1)+solve(i,r,counter+1));
    return ret;
}

int main(){
    scanf("%d",&n);
    scanf("%s",&s);
    memset(dp,-1,sizeof(dp));
    for(int i=0; i<n; i++)scanf("%d",&arr[i+1]);
    printf("%I64d",solve());
return 0;
}
