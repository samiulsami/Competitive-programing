#include<bits/stdc++.h>
using namespace std;

int coins[15]={10000,5000,2000,1000,500,200,100,50,20,10,1};

int to_int(string &s){
    int ret=0;
    for(int i=0,len=s.length(); i<len; i++){
        if(s[i]=='.')continue;
        ret+=s[i]-48;
        ret*=10;
    }
    return ret/10;
}

long long dp[30002][15];

long long solve(int i,int amount){
    if(amount==0)return 1;
    if(i==11 || amount<0)return 0;
    long long &ret = dp[amount][i];
    if(ret!=-1)return ret;
    return ret = solve(i,amount-coins[i])+solve(i+1,amount);
}

int main(){
    memset(dp,-1,sizeof(dp));
    //freopen("output.txt","w",stdout);
    string s;
    long long ans,tmp;
    int width;
    while(cin>>s){
        int n=to_int(s);
        if(!n)break;
        width=0;
        ans=solve(0,n);
        tmp=ans;
        while(tmp)width++,tmp/=10;
        width=17-width;
        for(int i=s.length(); i<6; i++)cout<<" ";
        cout<<s;
        for(int i=0; i<width; i++)cout<<" ";
        cout<<ans<<endl;
    }
return 0;
}
