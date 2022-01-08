#include<bits/stdc++.h>
using namespace std;

int dp[202][10005];
int dir[202][10005];
int arr[202];
int sum[202];
int n,cap;

int solve(int i=0, int amount1=cap, int amount2=cap){
    if(i==n || (amount1<=0 && amount2<=0))return 0;
    int &ret = dp[i][max(amount1,amount2)];
    if(~ret)return ret;
    int a=0,b=0;
    if(amount1-arr[i]>=0)a=solve(i+1,amount1-arr[i],amount2)+1;
    if(amount2-arr[i]>=0)b=solve(i+1,amount1,amount2-arr[i])+1;
    if(a>=b)ret=a,dir[i][max(amount1,amount2)]=1;
    else ret=b,dir[i][max(amount1,amount2)]=2;
    return ret;
}

int main(){
    int t;
    //freopen("output.txt","w",stdout);
    cin>>t;
    getchar();
    for(int cas=1; cas<=t; cas++){
        cin>>cap;
        cap*=100;
        n=0;
        while(cin>>arr[n],arr[n])n++;
        memset(dp,-1,sizeof(dp));
        memset(dir,-1,sizeof(dir));
        int ans=solve(0,cap,cap);
        cout<<ans<<endl;
        int i=0,amount1=cap,amount2=cap,amount=cap;
        while(dir[i][max(amount1,amount2)]!=-1 && i<ans && amount1>=0 && amount2>=0){
            amount=max(amount1,amount2);
            int &d = dir[i][amount];
            if(d==1)cout<<"port"<<endl,amount1-=arr[i];
            else cout<<"starboard"<<endl,amount2-=arr[i];
            i++;
        }
        if(cas!=t)cout<<endl;
        getchar();
    }
return 0;
}
