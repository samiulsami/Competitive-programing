#include<bits/stdc++.h>
using namespace std;

int n,x;
int arr[105];
int dp[105][5005];

int solve(int i, int sum){
    if(sum>5000)return sum;
    if(i==n)return 10000;
    int &ret=dp[i][sum];
    if(~ret)return ret;
    return ret=min(solve(i+1,sum+arr[i]),solve(i+1,sum));
}

int main(){
    //freopen("output.txt","w",stdout);
    while(cin>>n>>x,n||x){
        getchar();
        memset(dp,-1,sizeof(dp));
        for(int i=0; i<n; i++){
            char c;
            int tmp=0;
            while(c=getchar()){
                if(c=='.')continue;
                if(c=='\n')break;
                tmp+=c-48;
                tmp*=10;
            }
            tmp/=10;
            arr[i]=tmp;
        }
        int index=arr[x-1];
        arr[x-1]=0;
        cout<<fixed<<setprecision(2)<<((double)(index*100)/(double)solve(0,index))+1e-9<<endl;
    }
return 0;
}
