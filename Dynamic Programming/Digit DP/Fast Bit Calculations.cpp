#include<bits/stdc++.h>
using namespace std;

vector<int>num;
long long dp[32][32][2][2];

long long solve(int i, int sum, int prev, int k){
    if(i==(int)num.size())return sum;
    long long &ret=dp[i][sum][prev][k];
    if(~ret)return ret;
    int lim=k?num[i]:1;
    ret=0;
    for(int j=0; j<=lim; j++)
        ret+=solve(i+1,sum+(j&prev),j,(num[i]==j?k:0));
    return ret;
}

int main(){
    int t,n;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        memset(dp,-1,sizeof(dp));
        cin>>n;
        num.clear();
        while(n){
            num.push_back(n%2);
            n/=2;
        }
        reverse(num.begin(),num.end());
        cout<<"Case "<<cas<<": "<<solve(0,0,0,1)<<endl;
    }
return 0;
}
