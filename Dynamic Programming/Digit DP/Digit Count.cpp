#include<bits/stdc++.h>
using namespace std;

int n;
vector<int>nums;
int dp[12][12];

int solve(int i=0,int prev=0){
    if(i==n)return 1;
    int &ret=dp[i][prev];
    if(~ret)return ret;
    ret=0;
    for(int j=0; j<(int)nums.size(); j++){
        if(prev>0 && abs(nums[j]-prev)>2)continue;
        ret+=solve(i+1,nums[j]);
    }
    return ret;
}

int main(){
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        nums.clear();
        int m;
        cin>>m>>n;
        for(int i=0,x; i<m; i++){
            cin>>x;
            nums.push_back(x);
        }
        memset(dp,-1,sizeof(dp));
        cout<<"Case "<<cas<<": "<<solve()<<endl;
    }
return 0;
}
