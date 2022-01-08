#include<bits/stdc++.h>
using namespace std;

int Set(int n, int pos){return n|(1<<pos);}
int reset(int n, int pos){return n&~(1<<pos);}
bool check(int n, int pos){return (bool)(n&(1<<pos));}

int arr[15][15];
int dp[(1<<15)+2];
int n;

int solve(int mask=0){
    if(mask==(1<<n)-1)return 0;
    int &ret=dp[mask];
    if(~ret)return ret;
    ret=INT_MAX;
    for(int i=0; i<n; i++){
        if(check(mask,i))continue;
        int price=arr[i][i];
        for(int j=0; j<n; j++){
            if(i==j)continue;
            if(check(mask,j))price+=arr[i][j];
        }
        ret=min(ret,solve(Set(mask,i))+price);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n;
        for(int i=0; i<n; i++)for(int j=0; j<n; j++)cin>>arr[i][j];
        memset(dp,-1,sizeof(dp));
        cout<<"Case "<<cas<<": "<<solve()<<endl;
    }
return 0;
}
