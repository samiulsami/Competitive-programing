const int MOD = (1LL<<31)-1;
const int base = 1521+rng()%(1<<22);
int P[N];
int lim = N-2;

inline int mul(ll x, int b) {
	x*=b;
    if(x<MOD)return x;
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

inline int add(ll a, int b){a+=b; return a>=MOD?a-MOD:a;}
inline int sub(ll a, int b){a-=b; return a<0?a+MOD:a;}