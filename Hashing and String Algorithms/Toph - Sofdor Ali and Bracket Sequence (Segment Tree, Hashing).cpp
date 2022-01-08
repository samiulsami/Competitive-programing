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

string s;

struct data{
    int unusedL,unusedR,total;
    data(){unusedL=unusedR=total=0;}
    data(int a, int b, int c):unusedL(a),unusedR(b),total(c){}
}Tree[4*N];

data Combine(data a, data b){
    int newl,newr,newt;
    int newc = min(a.unusedL,b.unusedR);
    newt=a.total+b.total+newc;
    newr=a.unusedR+b.unusedR-newc;
    newl=a.unusedL+b.unusedL-newc;
    return data(newl,newr,newt);
}

void build(int node, int l, int r){
    if(l==r){
        if(s[l-1]=='(')Tree[node].unusedL++;
        else Tree[node].unusedR++;
    }
    else{
        int mid = (l+r)>>1;
        build(node<<1,l,mid);
        build(node<<1 | 1, mid+1, r);
        Tree[node] = Combine(Tree[node<<1], Tree[node<<1 | 1]);
    }
}

data query(int node, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    if(posr<=mid)return query(node<<1, l, mid, posl, posr);
    if(posl>mid)return query(node<<1 | 1, mid+1, r, posl, posr);
    return Combine(query(node<<1, l, mid, posl, posr), query(node<<1 | 1, mid+1, r, posl, posr));
}

int n;
inline bool valid(int l, int r){
    return (query(1,1,n,l,r).total*4==n);
}

const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
	ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod1) + (ret>>61);
	ret = (ret & mod1) + (ret>>61);
	return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = (ull)1554+(ull)rng()%(1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--)
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
};

void solve(int caseno){
    cin>>s;
    int len=s.length();
    n=len+len;
    s+=s;
    build(1,1,n);
    vector<int>indexes;
    for(int i=1; i<=len; i++){
        if(valid(i,i+len-1))indexes.push_back(i);
    }

    Hash H(s,n);

    if(indexes.empty()){
        cout<<-1<<endl;
        return;
    }

    int minInd= *min_element(all(indexes), [&](int a, int b){
        int low=1,high=len,mid;
        int x=1e9;
        while(low<=high){
            mid=(low+high)>>1;
            if(H.getHash(a,a+mid-1)==H.getHash(b,b+mid-1))low=mid+1;
            else{
                high=mid-1;
                x=min(x,mid);
            }
        }
        if(x==1e9)return a<b;
        return s[a+x-2]<s[b+x-2];
    });

    cout<<s.substr(minInd-1,len)<<endl;
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}
