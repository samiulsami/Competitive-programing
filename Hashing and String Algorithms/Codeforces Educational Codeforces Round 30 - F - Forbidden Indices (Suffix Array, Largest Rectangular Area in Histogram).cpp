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
const int N = 2e5+5;

int csum[N]={0};

namespace SuffixArray{
    ///Competitive Programming 3
    const int MAX_N=2e5+5;
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

    int L[MAX_N],R[MAX_N];
    stack<int>st;

    ll calc(){
        for(int i=0; i<n; i++){
            while(!st.empty() && LCP[st.top()]>=LCP[i])st.pop();
            if(st.empty())L[i]=0;
            else L[i]=st.top();
            st.push(i);
        }
        while(!st.empty())st.pop();

        for(int i=n-1; i>=0; i--){
            while(!st.empty() && LCP[st.top()]>=LCP[i])st.pop();
            if(st.empty())R[i]=n-1;
            else R[i]=st.top()-1;
            st.push(i);
        }

        ll ret=0;
        for(int i=0; i<n; i++){
           // cout<<s.substr(SA[i]);
            ll len=LCP[i];
            //pf(" %d %d\n",L[i],R[i]);
            ll cnt=(R[i]-L[i]+1)-csum[R[i]];
            if(L[i]>0)cnt+=csum[L[i]-1];
            //cout<<" "<<len<<" "<<cnt<<" "<<L[i]<<" "<<R[i]<<endl;
            ret=max(ret,len*cnt);
        }
        return ret;
    }

};



void solve(int caseno){
    string s,forbidden;
    int x;
    cin>>x;
    cin>>s>>forbidden;
    reverse(all(s));
    reverse(all(forbidden));
    s+="$";
    SuffixArray::init(s);
    for(int i=0; i<sz(forbidden); i++){
        if(forbidden[i]=='0')break;
        x--;
    }

    for(int i=0; i<SuffixArray::n; i++){
        if(forbidden[SuffixArray::SA[i]]=='1')csum[i]++;
        if(i)csum[i]+=csum[i-1];
    }

    cout<<max((ll)x,SuffixArray::calc())<<endl;

}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
