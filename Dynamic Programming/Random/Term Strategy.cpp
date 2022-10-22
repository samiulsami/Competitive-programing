#include<bits/stdc++.h>
using namespace std;

int n,m;
int arr[15][105];
int dp[15][105];

int solve(int i=0,int counter=m){
    if(i==n)return 0;
    if(counter==0)return INT_MIN;
    int &ret=dp[i][counter];
    if(~ret)return ret;
    ret=INT_MIN;
    for(int h=0; h<m; h++){
        while(arr[i][h]<5 && h<m)h++;
        if(h>=m)break;
        if(counter-h-1>=0)ret=max(ret,solve(i+1,counter-h-1)+arr[i][h]);
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)cin>>arr[i][j];
        memset(dp,-1,sizeof(dp));
        int ans=solve();
        if((ans/n)>=5)cout<<"Maximal possible average mark - "<<fixed<<setprecision(2)<<(double)ans/(double)n + (1e-9)<<"."<<endl;
        else cout<<"Peter, you shouldn't have played billiard that much."<<endl;
    }
return 0;
}
