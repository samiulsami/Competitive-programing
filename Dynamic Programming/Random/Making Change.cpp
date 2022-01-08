#include<bits/stdc++.h>
using namespace std;

int coin[6]={5,10,20,50,100,200};
int counter[6];
int dp1[10][1000];
int dp2[10][1000];

int solve2(int i, int amount){
    if(amount==0)return 0;
    if(i==6 || amount<0)return 100000;
    int &ret = dp2[i][amount];
    if(~ret)return ret;
    return ret = min(solve2(i+1,amount),solve2(i,amount-coin[i])+1);
}

int solve(int i, int amount){
    if(amount==0)return 0;
    if(i==6 || amount<0)return 100000;
    int &ret = dp1[i][amount];
    if(~ret)return ret;
    ret = 100000;
    for(int k=0; k<=counter[i]; k++)ret = min(ret,solve(i+1,amount-(k*coin[i]))+k);
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    memset(dp2,-1,sizeof(dp2));
    while(true){
        bool flag=0;
        for(int i=0; i<6; i++){
            cin>>counter[i];
            if(counter[i])flag=1;
        }
        if(!flag)break;
        double tmp;
        int target;
        cin>>tmp;
        tmp*=100;
        target = tmp+0.5;
        memset(dp1,-1,sizeof(dp1));
        int ans=solve(0,target);
        for(int i=target; i<=800; i+=5)
			ans = min(ans, solve(0,i)+solve2(0,i-target));
        cout<<setw(3)<<ans<<endl;
    }
return 0;
}
