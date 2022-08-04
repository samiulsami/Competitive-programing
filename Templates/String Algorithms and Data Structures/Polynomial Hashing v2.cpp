const int mod1 = (1LL<<31)-1;
const int base = 1521+rng()%(1<<22);
vector<int>P{1};

inline int mod(ll x) {
    if(x<mod1)return x;
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{///1 indexed
    vector<int>H;
    vector<int>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        while((int)P.size()<=n)P.push_back(mod(1LL*P.back()*base));
        H.resize(n+1);H[0]=0;
        R.resize(n+2);R[n+1]=0;R[0]=0;
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = mod((1LL*H[i]*base) + ((ll)s[i]));
            R[j-1] = mod((1LL*R[j]*base) + ((ll)s[j-2]));
         }
    }
    inline int fHash(int l, int r){
        int h = H[r] - mod(1LL*H[l-1] * P[r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline int rHash(int l, int r){
        int h = R[l] - mod(1LL*R[r+1] * P[r-l+1]);
        return (h<0?h+mod1:h);
    }
};