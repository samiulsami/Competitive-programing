#include<bits/stdc++.h>
using namespace std;

int t,n,k,A[105];
long long dp[10005];

int main(){
    scanf("%d",&t);
    int cas,i,j;
    for(cas=1; cas<=t; cas++){
        memset(dp, 0, sizeof(dp));
        dp[0]=1;
        scanf("%d%d",&n,&k);
        for(i=0; i<n; i++)scanf("%d",&A[i]);
        for(i=0; i<n; i++){
            for(j=1; j<=k; j++){
                    if(j-A[i]>=0){
                            dp[j]+=dp[j-A[i]];
                            dp[j]%=100000007;
                    }
            }
        }
        printf("Case %d: %lld\n", cas, dp[k]);
    }
return 0;
}
