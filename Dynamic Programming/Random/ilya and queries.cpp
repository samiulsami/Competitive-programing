#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int m,l,r;
    int dp[100005]={0};
    cin>>s>>m;
    for(int i=1,len=s.length(); i<len; i++)dp[i]+=dp[i-1]+(s[i]==s[i-1]);
    while(m--){
        cin>>l>>r;
        cout<<dp[r-1]-(dp[l-1]*(l!=1))<<endl;
    }
return 0;
}
