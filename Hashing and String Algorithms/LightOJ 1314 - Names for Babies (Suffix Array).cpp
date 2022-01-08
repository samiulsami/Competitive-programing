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
#define sii(x,y) scanf("d",&x,&y)
#define siii(x,y,z) scanf("d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("lld",&x,&y)
#define slll(x,y,z) scanf("lld%lld",&x,&y,&z)
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
    const int MAX_N=1e4+5;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;

    inline void countingSort(int k){
        int i, sum, maxi = max(130, n),t;
        memset(c, 0, sizeof c);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const string &s){
        int i,k,j,r;
        n=(int)s.size();
        for (i = 0; i < n; i++)RA[i]=s[i],SA[i]=i;
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
            j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
        }
    }

};


void solve(int caseno){
    string s;
    int p,q;
    cin>>s>>p>>q;
    s+="$";
    SuffixArray::init(s);
    ll ans=0;

    using namespace SuffixArray;
    for(int i=1; i<n; i++){
        int lower = max(SA[i]+LCP[i], SA[i]+p-1);
        int upper = min(SA[i]+q-1, n-2);
        //cout<<"LCP: "<<LCP[i]<<", "<<"upper: "<<upper<<", lower: "<<lower<<", suff: "<<s.substr(SA[i])<<endl;
        if(upper>=lower)ans+=(upper-lower+1);
    }

    cout<<"Case "<<caseno<<": "<<ans<<endl;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
