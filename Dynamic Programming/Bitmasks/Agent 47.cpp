#include<bits/stdc++.h>
using namespace std;

int Set(int n, int pos){return n|(1<<pos);}
bool check(int n, int pos){return (bool)(n&(1<<pos));}

int arr[20][20],hp[20],n;
int dp[(1<<15)+2];

int solve(int mask){
    if(mask==(1<<n)-1)return 0;
    int &ret=dp[mask];
    if(~ret)return ret;
    ret=INT_MAX;
    for(int i=0; i<n; i++){
        if(check(mask,i))continue;
        for(int j=0; j<n; j++){
            int dmg,shots;
            if(check(mask,j))dmg=max(1,arr[j][i]);
            else dmg=1;
            shots=hp[i]/dmg;
            if(hp[i]%dmg && dmg<hp[i])shots++;
            ret=min(ret,solve(Set(mask,i))+shots);
        }
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        memset(dp,-1,sizeof(dp));
        cin>>n;
        string s;
        for(int i=0; i<n; i++)cin>>hp[i];
        for(int i=0; i<n; i++){
            cin>>s;
            for(int j=0; j<n; j++)arr[i][j]=s[j]-48;
        }
        cout<<"Case "<<cas<<": "<<solve(0)<<endl;
    }
return 0;
}
