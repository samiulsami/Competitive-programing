#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl;
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
const int N = 10005;

int SA[N],tmp[N],RA[N];
int LCP[N];
string s;

void init(){
    int n=(int)s.size(),k;
    for(int i=0; i<n; i++){
        SA[i]=i;
        RA[i]=s[i];
    }
    auto cmp = [&](int &a, int &b)->bool{
        if(RA[a]!=RA[b])return RA[a]<RA[b];
        if(a+k<n && b+k<n)return RA[a+k]<RA[b+k];
        return a>b;
    };
    for(k=1; ;k<<=1){
        sort(SA,SA+n,cmp);
        tmp[0]=0;
        for(int i=1; i<n; i++)tmp[i]=tmp[i-1]+cmp(SA[i-1],SA[i]);
        for(int i=0; i<n; i++)RA[SA[i]]=tmp[i];
        if(tmp[n-1]==n-1)break;
    }
    for(int i=0; i<n; i++)tmp[SA[i]]=i;

    k=0;
    for(int i=0; i<n; i++){
        int ind = tmp[i];
        if(ind==0){
            k=0;
            continue;
        }
        int j = SA[ind-1];
        while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;
        LCP[tmp[i]]=k;
        if(k>0)k--;
    }
}


void solve(int caseno){
    string b;
    cin>>b;
    s+=b;
    s+="$";
    int x=s.length()-1;
    cin>>b;
    s+=b;
    s+="#";
    init();
    int n = s.length();

    bool found=0;
    int ans=1e9;
    for(int i=1; i<n; i++){
        if(LCP[i]>LCP[i-1] && LCP[i+1]<LCP[i]){
            int a=SA[i-1];
            int b=SA[i];
            if(min(a,b)<=x && max(a,b)>x){
                found=1;
                ans=min(ans,max(LCP[i-1],LCP[i+1])+1);
            }
        }
    }
    if(!found)ans=-1;
    cout<<ans<<endl;

}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
