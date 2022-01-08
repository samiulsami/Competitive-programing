#include<bits/stdc++.h>
using namespace std;

int n,maxC,minC;
long long dp[301][301][301];

long long solve(int i, int amount, int counter){
    if(amount==0)return 1;
    if(i==301 || amount<0 || counter==0)return 0;
    long long &ret = dp[i][amount][counter];
    if(~ret)return ret;
    return ret = solve(i+1, amount, counter)+solve(i, amount-i, counter-1);
}

int main(){
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    memset(dp,-1,sizeof(dp));
    char s[100];
    while(scanf(" %[^\n]",s)!=EOF){
        int i=0;
        int arr[3]={0};
        for(int j=0; s[j]; j++){
            if(s[j]==' ')j++,i++;
            arr[i]+=s[j]-48;
            arr[i]*=10;
        }
        n=arr[0]/10;
        minC=min(300,arr[1]/10);
        maxC=min(300,arr[2]/10);
        if(n==0 && minC==0)printf("1\n");
        else if(i==0)printf("%lld\n",solve(1,n,300));
        else if(i==1)printf("%lld\n",solve(1,n,minC));
        else printf("%lld\n",solve(1,n,maxC)-solve(1,n,max(0,minC-1)));
    }
return 0;
}
