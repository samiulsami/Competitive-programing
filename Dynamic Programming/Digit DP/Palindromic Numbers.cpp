#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][20][2][2][2];//index, index2, non-zero digit found?, <num?, digits outside limit?
vector<int>num;

ll f(int i, int j, bool nz, bool k, bool l){
    if(i>j)return (k&&l)?0:1;
    ll &ret = dp[i][j][nz][k][l];
    if(~ret)return ret;
    ret=0;
    int lim=k?num[i]:9;
    for(int x=0; x<=lim; x++){
        if((!x&&!nz)||i==j)ret+=f(i+1,j,0,num[i]==x?k:0,l);
        else if(x==num[j])ret+=f(i+1,j-1,nz|(x>0),num[i]==x?k:0,l);
        else ret+=f(i+1,j-1,nz|(x>0),num[i]==x?k:0,(x>num[j]));
    }
    return ret;
}

ll solve(ll x){
    num.clear();
    memset(dp,-1,sizeof(dp));
    while(x){
        num.push_back(x%10);
        x/=10;
    }
    reverse(num.begin(),num.end());
    return f(0,(int)num.size()-1, 0, 1, 0);
}

int main(){
    //freopen("output.txt","w",stdout);
    ll a,b;
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>a>>b;
        if(a<b)swap(a,b);
        a=solve(a);
        if(b)b=solve(b-1);
        cout<<"Case "<<cas<<": "<<a-b<<endl;
    }
return 0;
}
