#include<bits/stdc++.h>
using namespace std;

struct dimsums{
    int val,sum;
}arr[105];

int n,x,tea,k;
int dp[105][10005][25];

int solve(int i=0,int val=n*tea,int counter=0){
    if(i==k)return 0;
    int &ret = dp[i][val][counter];
    if(~ret)return ret;
    ret=0;
    for(int j=0; counter+j<=2*n && j<=2; j++){
        int newval = val+(j*arr[i].val);
        int tmpval = ceil((double)newval*1.1 - 1e-9)+0.5;
        if(tmpval>(n*x))continue;
        ret=max(ret,solve(i+1,newval,counter+j)+(j*arr[i].sum));
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    while(cin>>n>>x>>tea>>k,n||x||tea||k){
        n++;
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<k; i++){
            cin>>arr[i].val;
            arr[i].sum=0;
            for(int j=0,in; j<n; j++)cin>>in,arr[i].sum+=in;
        }
        cout<<fixed<<setprecision(2)<<(double)solve()/(double)n + 1e-9<<endl;
    }
return 0;
}
