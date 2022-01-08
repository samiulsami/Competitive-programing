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

namespace shittySA{
    const int MAX_N=1e5+5;
    int SA[MAX_N],tmp[MAX_N],RA[MAX_N],n;
    void init(vector<int> &arr){
        n=(int)arr.size();
        int k;
        for(int i=0; i<n; i++)RA[i]=arr[i],SA[i]=i;
        auto cmp = [&](int &a, int &b)->bool{
            if(RA[a]^RA[b])return RA[a]<RA[b];
            return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
        };
        for(k=1; k<n ;k<<=1){
            sort(SA,SA+n,cmp);
            tmp[0]=0;
            for(int i=1; i<n; i++)tmp[i]=tmp[i-1]+cmp(SA[i-1],SA[i]);
            for(int i=0; i<n; i++)RA[SA[i]]=tmp[i];
            if(tmp[n-1]==n-1)break;
        }
    }
}

pii Tree[4*N];

void build(int node, int l, int r){
    if(l==r)Tree[node]=pii(shittySA::RA[l-1],l);
    else{
        int mid = (l+r)>>1;
        build(node<<1,l,mid);
        build(node<<1 | 1,mid+1,r);
        Tree[node] = min(Tree[node<<1],Tree[node<<1 | 1]);
    }
}

pii query(int node, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    if(posl>mid)return query(node<<1 | 1,mid+1,r,posl,posr);
    if(posr<=mid)return query(node<<1,l,mid,posl,posr);
    return min(query(node<<1,l,mid,posl,posr), query(node<<1 | 1,mid+1,r,posl,posr));
}

void solve(int caseno){
    int n,q;
    sii(n,q);
    vector<int> arr(n+1);
    for(int i=0; i<n; i++)si(arr[i]);
    shittySA::init(arr);
    build(1,1,n);

    int l,r;
    pf("Case %d:\n",caseno);
    while(q--){
        sii(l,r);
        pf("%d\n",query(1,1,n,l,r).second);
    }

}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
