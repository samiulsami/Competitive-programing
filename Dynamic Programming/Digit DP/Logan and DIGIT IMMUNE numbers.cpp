#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int>num;
ll dp[19][5][7][9][16][2];

ll f(int i, int five, int sev, int nine, int mask, int k, int nz){
    if(i==-1){
        if(nz)return 0;
        if(mask&1 && nine%3==0)return 0;
        if(mask&(1<<1) && five%5==0)return 0;
        if(mask&(1<<2) && sev%7==0)return 0;
        if(mask&(1<<3) && nine%9==0)return 0;
        return 1;
    }
    ll &ret = dp[i][five][sev][nine][mask][nz];
    if(ret!=-1 && !k)return ret;
    ll ans=0;
    int lim = k?num[i]:9;
    for(int j=3; j<=lim; j+=2){
        int newmask=mask;
        if(j==3)newmask|=1;
        else if(j==5)newmask|=(1<<1);
        else if(j==7)newmask|=(1<<2);
        else if(j==9)newmask|=(1<<3);
        ans+=f(i-1, (five*10+j)%5, (sev*10+j)%7, (nine*10+j)%9, newmask, num[i]==j?k:0, 0);
    }
    if(nz)ans+=f(i-1, five, sev, nine, mask, 0, 1);
    if(!k)ret=ans;
    return ans;
}


ll solve(ll x){
    num.clear();
    while(x){
        num.push_back(x%10);
        x/=10;
    }
    return f((int)num.size()-1, 0, 0, 0, 0, 1, 1);
}

int main(){
    memset(dp,-1,sizeof(dp));
    ll q,a,b,k;
    cin>>q;
    while(q--){
        cin>>a>>b>>k;
        k+=solve(a-1);
        if(k>solve(b)){
            cout<<-1<<endl;
            continue;
        }
        ll low=a,high=b,mid,tmp;
        while(low<=high){
            mid=(low)+(high-low)/2;
            tmp=solve(mid);
            if(tmp<k)low=mid+1;
            else high=mid-1;
        }
        cout<<low<<endl;
    }
return 0;
}
