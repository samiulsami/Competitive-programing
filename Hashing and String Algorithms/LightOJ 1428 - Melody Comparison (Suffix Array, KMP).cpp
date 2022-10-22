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
const int N = 1e5+5;

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=5e4+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const string &s){
        int i,k,r;
        n=(int)s.size();
        for (i = 0; i < n; i++)RA[i] = s[i];
        for (i = 0; i < n; i++)SA[i] = i;
        for (k = 1; k < n; k <<= 1){
            countingSort(k);
            countingSort(0);
            invSA[SA[0]] = r = 0;
            for (i = 1; i < n; i++)invSA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
            for (i = 0; i < n; i++)RA[i] = invSA[i];
            if (RA[SA[n-1]] == n-1) break;
        }
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            int j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
        }
    }
};

int pi[50004];
int nxt[50004];
void solve(int caseno){
    string a,b;
    cin>>a>>b;
    a+="$";
    pi[0]=0;
    for(int i=1,j; i<sz(b); i++){
        j=pi[i-1];
        while(j && b[i]!=b[j])j=pi[j-1];
        if(b[i]==b[j])pi[i]=j+1;
        else pi[i]=0;
    }

    for(int i=0; i<=sz(a); i++)nxt[i]=1e9;
    for(int i=0,j=0; i<sz(a); i++){
        while(j && b[j]!=a[i])j=pi[j-1];
        if(a[i]==b[j])j++;
        if(j==sz(b)){
            nxt[i]=i;
            j=pi[j-1];
        }
    }

    for(int i=sz(a)-1; i>=0; i--){
        nxt[i]=min(nxt[i],nxt[i+1]);
    }
    for(int i=0; i<sz(a); i++){
            if(i+sz(b)-1>=sz(a))nxt[i]=1e9;
            else nxt[i]=nxt[i+sz(b)-1];
    }

    using namespace SuffixArray;

    init(a);
    ll ans=0;
    for(int i=1; i<n; i++){
       //cout<<"start: "<<SA[i]<<" LCP: "<<LCP[i]<<", nxt: "<<nxt[SA[i]]<<" "<<a.substr(SA[i])<<" ";
       int ind=nxt[SA[i]];
       int take=0;
       if(ind+1<=SA[i]+LCP[i])take=0;
       else if(ind==1e9)take=n-SA[i]-LCP[i]-1;
       else take=ind-SA[i]-LCP[i];
       //if(sz(b)==1 && b[0]==a[SA[i]])take=0;
       ans+=take;
      // cout<<take<<endl;
    }
    cout<<"Case "<<caseno<<": "<<ans<<endl;

}

int main(){
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
