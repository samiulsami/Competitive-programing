#include<bits/stdc++.h>
using namespace std;

int n;
int arr[25],tmp[25];
int dp[25][25];

int solve(int i=0, int j=0){
    if(i==n || j==n)return 0;
    int &ret = dp[i][j];
    if(~ret)return ret;
    return ret=max((arr[i]==tmp[j])+solve(i+1,j+1),max(solve(i+1,j),solve(i,j+1)));
}

bool read(int *a){
    for(int i=0,in; i<n; i++){
            if(scanf("%d",&in)!=1)return 0;
            a[in-1]=i;
    }
    return 1;
}

int main(){
    //freopen("output.txt","w",stdout);
    cin>>n;
    read(arr);
    while(read(tmp)){
        memset(dp,-1,sizeof(dp));
        cout<<solve()<<endl;
    }

return 0;
}
