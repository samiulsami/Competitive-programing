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
const uint64_t base1 = (uint64_t)1541 + (uint64_t)rng()%(uint64_t)(1<<22);
vector<uint64_t>P{1};

struct Hash{///1 indexed
    vector<uint64_t>H;
    vector<uint64_t>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
        n = int(s.size());
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        H.resize(n+1);H[0]=0;
        R.resize(n+2);R[n+1]=0;R[0]=0;
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
            R[j-1] = hashAdd(hashmodmul(R[j], base1), (uint64_t)s[j-2]);
        }
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
    inline uint64_t rHash(int l, int r){return hashSub(R[l], hashmodmul(R[r+1], P[r-l+1]));}
};