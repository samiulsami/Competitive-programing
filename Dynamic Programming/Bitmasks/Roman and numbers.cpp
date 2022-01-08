#include<bits/stdc++.h>
using namespace std;

string n;
long long dp[(1<<18)+2][105],m;
long long powers[22];

long long solve(int mask, int rem){
    if(mask==(1<<n.length())-1)return rem==0;
    long long &ret=dp[mask][rem];
    if(ret!=-1)return ret;

    int power_count=0;
    for(int i=0; i<n.length(); i++)if(mask&(1<<i))power_count++;

    ret=0;
    bool vis[10]={0};
    for(int i=0; i<n.length(); i++){
        int val=n[i]-48;
        if(mask==0 && val==0)continue;//no leading zeroes
        if(mask&(1<<i) || vis[val])continue;
        vis[val]=1;
        int newMask = mask|(1<<i);
        int newRem = (rem+(val*powers[power_count]))%m;
        ret+=solve(newMask,newRem);
    }
    return ret;
}

int main(){
    memset(dp,-1,sizeof(dp));
    cin>>n>>m;
    powers[0]=1;
    for(int i=0; i<18; i++)powers[i+1]=powers[i]*10;
    reverse(powers,powers+n.length());
    cout<<solve(0,0);
return 0;
}
