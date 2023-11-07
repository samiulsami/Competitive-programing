mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const uint64_t mod1 = (1uLL<<61) - 1;
inline uint64_t hashmodmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod1) + (ret>>61);
    ret = (ret & mod1) + (ret>>61);
    return ret-1;
}
inline uint64_t hashAdd(uint64_t a, uint64_t b){a+=b;return a>=mod1?a-mod1:a;}
inline uint64_t hashSub(uint64_t a, uint64_t b){a-=b;return a>=mod1?a+mod1:a;}
const uint64_t base1 = uint64_t(1541) + (uint64_t(rng())%(1uLL<<60));
vector<uint64_t>P{1};

struct Hash{///0 indexed
    vector<uint64_t>H,R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
        n = int(s.size());
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        H.resize(n+1,0);
        R.resize(n+2,0);
        for(int i=0; i<n; i++){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
            R[n-i] = hashAdd(hashmodmul(R[n-i+1], base1), (uint64_t)s[n-i-1]);
        }
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r+1], hashmodmul(H[l], P[r-l+1]));}
    inline uint64_t rHash(int l, int r){return hashSub(R[l+1], hashmodmul(R[r+2], P[r-l+1]));}
};