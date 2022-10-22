#include<bits/stdc++.h>
using namespace std;

int Set(int n, int pos){return n|(1<<pos);}
bool check(int n, int pos){return (bool)(n&(1<<pos));}

int dp[(1<<20)+2];
int arr[22];
int n;

int solve(int mask=0){
    if(mask>=(1<<n)-1)return 0;
    int &ret = dp[mask];
    if(~ret)return ret;
    ret=2000000;
    for(int i=0; i<n; i++){
        int newmask=mask;
        newmask=Set(newmask,i);
        newmask=Set(newmask,(i+1)%n);
        newmask=Set(newmask,(i+2)%n);
        int dmg=0;
        for(int j=0; j<n; j++)if(!check(newmask,j))dmg+=arr[j];
        ret=min(ret,solve(newmask)+dmg);
    }
    return ret;
}

int main(){
    while(cin>>n){
        for(int i=0; i<n; i++)cin>>arr[i];
        memset(dp,-1,sizeof(dp));
        cout<<solve(0)<<endl;
    }
return 0;
}
