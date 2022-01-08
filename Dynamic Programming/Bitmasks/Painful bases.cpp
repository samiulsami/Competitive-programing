#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[(1<<16)+2][25];
map<ll,ll>val;
ll powers[20];
string s;
ll n,m;

ll solve(int mask, int rem){
    if(mask==(1<<s.length())-1)return rem==0;
    ll &ret=dp[mask][rem];
    if(ret!=-1)return ret;
    int power_count=0;
    for(int i=0; i<s.length(); i++)if(mask&(1<<i))power_count++;
    ret=0;
    for(int i=0; i<s.length(); i++){
        ll x=val[s[i]];
        if(mask&(1<<i))continue;
        ret+=solve(mask|(1<<i), (rem+powers[power_count]*x)%m);
    }
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    int t;
    for(int i='0'; i<='9'; i++)val[i]=i-'0';
    for(int i='A'; i<='F'; i++)val[i]=i-'A'+10;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        memset(dp,-1,sizeof(dp));
        cin>>n>>m;
        cin>>s;
        powers[0]=1;
        for(int i=0; i<=18; i++)powers[i+1]=(powers[i]%m)*n;
        reverse(powers,powers+s.length());
        cout<<"Case "<<cas<<": "<<solve(0,0)<<endl;
    }
return 0;
}
