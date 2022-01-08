#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
const int N=2e5+5;
const int MOD=(1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};
int P[N];
char s[N];
int n;
inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}
struct segTree{
    int n;
    bool isReverse;
    vector<int>Tree;
    segTree(int n, bool isReverse):n(n),isReverse(isReverse),Tree(2*n){}
    void update(int ind, int c){/// 0 indexed
        if(isReverse)Tree[ind+n] = mod(1LL*c*P[n-ind-1]);
        else Tree[ind+n] = mod(1LL*c*P[ind]);
        ind+=n;
        for(;ind>1; ind>>=1)Tree[ind>>1] = mod(1LL*Tree[ind]+1LL*Tree[ind^1]);
    }
    int query(int l, int r){///0 indexed
        if(l>r)return 0;
        if(l<0 || r<0 || l>=n || r>=n)return 0;
        l+=n;
        r+=n+1;
        int ret=0;
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=mod(1LL*ret+1LL*Tree[l++]);
            if(r&1)ret=mod(1LL*ret+1LL*Tree[--r]);
        }
        return ret;
    }
    inline int getHash(int l, int r){///1 indexed
        if(l>r)return 0;
        if(l<=0 || r<=0 || l>n || r>n)return 0;
        l--,r--;
        if(isReverse)return mod(1LL*query(l,r)*P[l]);
        return mod(1LL*query(l,r)*P[n-r-1]);
    }
};
