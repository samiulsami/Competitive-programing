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
    const int MAX_N=3*5005;
    const int K=15;
    int SA[MAX_N],LCP[MAX_N],invSA[MAX_N];
    int RA[MAX_N],c[MAX_N],n;
    int lgval[MAX_N];
    int Table[K][MAX_N]={0};

    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
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
            Table[0][invSA[i]]=k;
        }
        lgval[0]=lgval[1]=0;
        for(i=2; i<MAX_N; i++)lgval[i]=lgval[i>>1]+1;
        for(i=1; i<K; i++){
            for(j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }

    inline int lcp(int i, int j){
        int lg = lgval[j-i+1];
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
};


int mark[3*5005];

void solve(int caseno){
    char ch=1;
    string a,b;
    vector<pii>lengths;
    int x,y;
    for(int i=0; i<3; i++){
        cin>>b;
        a+=b+ch++;
        lengths.push_back(pii(a.length()-1,i));
    }

    SuffixArray::init(a);
    using namespace SuffixArray;

    for(int i=0; i<n; i++)
        mark[i] = (*lower_bound(all(lengths),pii(i,0))).second;

    int ans=0;
    array<int,3>cnt;
    fill(all(cnt),0);
    int distinct=0;

    for(int i=0,l=0; i<n; i++){
        //cout<<a.substr(SA[i])<<" "<<mark[SA[i]]<<endl;
        if(++cnt[mark[SA[i]]]==1)distinct++;
        while(l<i && distinct==3){
            ans=max(ans,lcp(l+1,i));
            if(--cnt[mark[SA[l++]]]==0)distinct--;
        }
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
