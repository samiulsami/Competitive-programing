#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[19][4][2];
vector<int>num;
int len;

ll f(int i, int sum, int k){
    if(sum>3)return 0;
    if(i==len)return (sum<=3);
    ll &ret = dp[i][sum][k];
    if(~ret)return ret;
    int lim=k?num[i]:9;
    ret=0;
    for(int j=0; j<=lim; j++)
        ret+=f(i+1, sum+(j>0), num[i]==j?k:0);
    return ret;
}

int main(){
    ll t,l,r;
    cin>>t;
    while(t--){
        memset(dp,-1,sizeof(dp));
        cin>>l>>r;
        num.clear();
        l--;
        while(l){
            num.push_back(l%10);
            l/=10;
        }
        reverse(num.begin(),num.end());
        len=num.size();
        l=f(0,0,1);
        num.clear();
        while(r){
            num.push_back(r%10);
            r/=10;
        }
        reverse(num.begin(), num.end());
        len=num.size();
        memset(dp,-1,sizeof(dp));
        r=f(0,0,1)-l;
        cout<<r<<endl;
    }

return 0;
}
