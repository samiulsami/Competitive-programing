#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int>numL,numR;
ll dp[19][2][2][2]; //index, non-zero digit used yet?, greater than numL?, less than numR?
ll dir[19][2][2][2];
int len;

ll f(int i, int z, int x, int y){
    if(i==len)return z?1:0;
    ll &ret = dp[i][z][x][y];
    if(~ret)return ret;
    int lower_lim = x?numL[i]:0;
    int upper_lim = y?numR[i]:9;
    ret=0;
    ll a;
    for(int j=lower_lim; j<=upper_lim; j++){
        ll m = (z|(j>0))?j:1LL;
        a = m*f(i+1, z|(j>0), numL[i]==j?x:0, numR[i]==j?y:0);
        if(a>ret || dir[i][z][x][y]==-1){
            ret=a;
            dir[i][z][x][y]=j;
        }
    }
    return ret;
}

int main(){
    ll a,b;
    memset(dp,-1,sizeof(dp));
    memset(dir,-1,sizeof(dir));
    cin>>a>>b;
    while(a){
        numL.push_back(a%10);
        a/=10;
    }
    while(b){
        numR.push_back(b%10);
        b/=10;
    }
    while(numR.size()>numL.size())numL.push_back(0);
    reverse(numR.begin(),numR.end());
    reverse(numL.begin(),numL.end());
    len=numR.size();
    f(0,0,1,1);
    int i=0,j,z=0,x=1,y=1;
    bool first=1;
    while(dir[i][z][x][y]!=-1 && i<len){
        j=dir[i][z][x][y];
        z=z|(j>0);
        x=numL[i]==j?x:0;
        y=numR[i]==j?y:0;
        i++;
        if(j>0)first=0;
        if(!first)cout<<j;
    }
return 0;
}


