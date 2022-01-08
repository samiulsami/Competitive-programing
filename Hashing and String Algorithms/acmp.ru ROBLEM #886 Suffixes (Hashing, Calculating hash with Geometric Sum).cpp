#include<bits/stdc++.h>
using namespace std;
/// acmp.ru PROBLEM #886 Suffixes
typedef int64_t ll;
typedef uint64_t ull;

seed_seq seq{
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}

const int _hashCnt=2;
const int MOD = (1LL<<31)-1;
const int bases[_hashCnt] = {rand(11887,1<<21),rand(15661,1<<22)};

inline int mod(ull x) {
        x+=MOD;
        x=(x>>31)+(x&MOD);
        return int((x>>31)+(x&MOD));
}

inline ull bigmod(ull x, ull pw){
    if(pw==0)return 1;
    x=mod(x);
    pw=mod(pw);
    ull ret=1;
    while(pw){
        if(pw&1)ret = mod(ret*x);
        x = mod(x*x);
        pw>>=1;
    }
    return ret;
}

vector<int>P[_hashCnt];

struct Hash{
    vector<int>H[_hashCnt];
    int n;
    inline void initP(int ind){
        while((int)P[ind].size()<=n){
            if(P[ind].empty())P[ind].push_back(1);
            else P[ind].push_back(mod(1LL*P[ind].back()*bases[ind]));
        }
    }
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            initP(ind);
            H[ind].resize(n+1);H[ind][0]=0;
            for(int i=0; i<n; i++){
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));
            }
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+MOD:h);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};

char s[int(1e5+5)];
inline int readline(char *st){
    int len=0;
    while((st[len]=getchar())!='\n')len++;
    st[len]='\0';
    return len;
}

int gSum(ll r, ll n){
    ll numerator = bigmod(r,n)-1;
    if(numerator<0)numerator+=MOD;
    ll denominator = bigmod(r-1,MOD-2);
    numerator = mod(numerator*denominator);
    return numerator;
}

int main() {
    int len = readline(s);
    reverse(s,s+len);
    Hash a(s,len);

    int sh1 = a.singleHash(1,len,0);
    int sh2 = a.singleHash(1,len,1);

    int ans=1;

    ///extend each prefix(since the string is reversed) and original string to length n*m, then compare hashes
    for(int i=1; i<len; i++){
        ///suffix hash
        int h1 = a.singleHash(1,i,0);
        ll b1 = bigmod(bases[0],i);
        int G1 = gSum(b1,len);
        h1 = mod(1LL*h1*G1);

        ll b2 = bigmod(bases[1],i);
        int h2 = a.singleHash(1,i,1);
        int G2 = gSum(b2,len);
        h2 = mod(1LL*h2*G2);

        ll pH = ((ll)h1<<32)^(ll)h2;

        ///original string hash
        b1 = bigmod(bases[0],len);
        G1 = gSum(b1,i);
        h1 = mod(1LL*sh1*G1);

        b2 = bigmod(bases[1],len);
        G2 = gSum(b2,i);
        h2 = mod(1LL*sh2*G2);

        ll oH = ((ll)h1<<32)^(ll)h2;

        if(pH==oH)ans++;
    }

    printf("%d\n",ans);

return 0;
}
