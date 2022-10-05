#include <bits/stdc++.h>
using namespace std;

const int N = 2e6+5;
const int MOD = (1LL<<31)-1;
const int base = 1523;
int P[N];

typedef int64_t ll;

inline int mod(ll x){
    if(x<MOD)return x;
    x+=MOD;
    x = (x>>31)+(x&MOD);
    return int((x>>31) + (x&MOD));
}

struct nd{
    int total,unusedL,unusedR;
}Tree[4*N];
string s;

inline nd Combine(nd L, nd R){
    nd ret;
    int t = min(L.unusedL, R.unusedR);
    ret.unusedL = L.unusedL + R.unusedL - t;
    ret.unusedR = R.unusedR + L.unusedR - t;
    ret.total = L.total + R.total + t;
    return ret;
}

void build(int node, int l, int r){
    if(l==r){
        Tree[node]={0,0,0};
        if(s[l-1]=='(')Tree[node].unusedL=1;
        else Tree[node].unusedR=1;
    }
    else{
        int mid = (l+r)>>1;
        build(node<<1, l, mid);
        build(node<<1|1, mid+1, r);
        Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
    }
}

nd query(int node, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    if(posl>mid)return query(node<<1|1, mid+1, r, posl, posr);
    if(posr<=mid)return query(node<<1, l, mid, posl, posr);
    return Combine(query(node<<1, l, mid, posl, posr), query(node<<1|1, mid+1, r, posl, posr));
}

struct Hash{/// 1 indexed
    vector<int>H;
    int n;
    Hash(){}
    Hash(string &s){
        n = s.size();
        H.resize(n+1);H[0]=0;
        for(int i=0; i<n; i++)
            H[i+1] = mod((1LL*H[i]*base) + (ll)s[i]);
    }
    inline int fHash(int l, int r){
        int h = H[r] - mod(1LL*H[l-1] * P[r-l+1]);
        return (h<0?h+MOD:h);
    }
};

void solve(int casenum)
{
    cin>>s;
    int n = s.length();
    s+=s;
    build(1,1,n+n);
    Hash H(s);

    vector<int>valid;
    int mx=N+N+N;
    for(int i=1; i<=n; i++){
        nd cur = query(1,1,n+n,i,i+n-1);
        if(mx>cur.unusedL+cur.unusedR)mx = cur.unusedL + cur.unusedR;
    }

    for(int i=1; i<=n; i++){
        nd cur = query(1,1,n+n,i,i+n-1);
        if(mx == (cur.unusedL + cur.unusedR))valid.push_back(i);
    }

    int ans = *min_element(valid.begin(), valid.end(), [&](int l, int r)->bool{
        auto L = query(1,1,n+n,l,l+n-1);
        auto R = query(1,1,n+n,r,r+n-1);
        if(L.unusedR != R.unusedR)return L.unusedR > R.unusedR;
        if(H.fHash(l,l+n-1) == H.fHash(r,r+n-1))return 0;

        int low = 1, high = n, mid,cur=-1;
        while(low<=high){
            mid = (low+high)>>1;
            if(H.fHash(l, l+mid-1) == H.fHash(r, r+mid-1))low=mid+1;
            else{
                cur = mid;
                high=mid-1;
            }
        }

        return s[l+cur-2] < s[r+cur-2];
    });

    auto cur = query(1,1,n+n, ans, ans+n-1);
    string out;
    for(int i=0; i<cur.unusedR; i++)out.push_back('(');
    for(int i=ans; i<=ans+n-1; i++)out.push_back(s[i-1]);
    for(int i=0; i<cur.unusedL; i++)out.push_back(')');

    cout<<out;

}

int main()
{
    P[0]=1;

    for(int i=1; i<N; i++){
            P[i] = mod(1LL*P[i-1]*base);

    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin>>t;
    for(int tt=1; tt<=t; tt++){
        solve(tt);
    }
    return 0;
}

/*

1
1 1 200 3

*/