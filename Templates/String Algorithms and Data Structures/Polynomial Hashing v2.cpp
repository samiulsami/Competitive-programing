const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};

vector<int>P[_hashCnt];

inline int mod(ll x) {
    if(x<mod1)return x;
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{
    vector<int>H[_hashCnt];
    vector<int>R[_hashCnt];
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
            R[ind].resize(n+2);R[ind][n+1]=0;R[ind][0]=0;
            for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));
                R[ind][j-1] = mod((1LL*R[ind][j]*bases[ind]) + ((ll)s[j-2]));
            }
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll getHash(int l, int r){return _hashCnt==1?singleHash(l,r):combineHash(singleHash(l,r,0), singleHash(l,r,1));}
    inline int singleReverseHash(int l, int r, int ind=0){
        int h = R[ind][l] - mod(1LL*R[ind][r+1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll reverseHash(int l, int r){return _hashCnt==1?singleReverseHash(l,r):combineHash(singleReverseHash(l,r,0), singleReverseHash(l,r,1));}
};
