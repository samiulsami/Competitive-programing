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
const ull base1 = (ull)1541 + (ull)rng()%(ull)(1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    vector<ull>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1),R(n+2){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
            R[j-1] = hashAdd(hashmodmul(R[j], base1), (ull)s[j-2]);
        }
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
    ull reverseHash(int l, int r){return hashSub(R[l], hashmodmul(R[r+1], P[r-l+1]));}
};
