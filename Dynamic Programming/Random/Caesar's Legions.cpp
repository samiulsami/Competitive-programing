#include<bits/stdc++.h>
using namespace std;

int n1,n2,k1,k2;
const long long MOD = 100000000;

long long dp[105][105][15][15];

long long solve(int i=n1, int j=n2, int swords=0, int horses=0){//sword=1 , horse=0
    if(i==0 && j==0)return 1;
    if(swords>n1 || horses>n2)return 0;
    long long &ret = dp[i][j][swords][horses];
    if(ret!=-1)return ret;
    ret = 0;
    if(swords<k1 && i>0)ret+=solve(i-1, j, swords+1, 0)%MOD;
    if(horses<k2 && j>0)ret+=solve(i, j-1, 0, horses+1)%MOD;
    return ret%MOD;
}

int main(){
    memset(dp, -1, sizeof(dp));
    cin>>n1>>n2>>k1>>k2;
    cout<<solve()<<endl;
return 0;
}
