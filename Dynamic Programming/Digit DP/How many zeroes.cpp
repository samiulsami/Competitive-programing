#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[33][33][2][2];
int vis[33][33][2][2]={0};
int color=0;
vector<int>num;
int len;

ll f(int i, int sum, bool nz, bool k){
    if(i==len)return sum;
    ll &ret = dp[i][sum][nz][k];
    if(vis[i][sum][nz][k]==color)return ret;
    vis[i][sum][nz][k]=color;
    ret=0;
    int lim=k?num[i]:9;
    for(int j=0; j<=lim; j++)
        ret+=f(i+1, (int)nz*(sum+(j==0)), nz|(j>0), num[i]==j?k:0);
    return ret;
}

int main(){
    //freopen("output.txt","w",stdout);
    ll t,n,nn,m;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        cin>>n>>m;
        num.clear();
        nn=n;
        if(n>0)n--;
        while(n){
            num.push_back(n%10);
            n/=10;
        }
        len=num.size();
        reverse(num.begin(),num.end());
        color++;
        if(nn!=0)nn=f(0,0,0,1)+1;
        num.clear();
        while(m){
            num.push_back(m%10);
            m/=10;
        }
        len=num.size();
        reverse(num.begin(),num.end());
        color++;
        m=f(0,0,0,1)+1;
        cout<<"Case "<<cas<<": "<<m-nn<<endl;
    }
return 0;
}
