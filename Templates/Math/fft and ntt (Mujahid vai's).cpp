NTT ntt(mod);
vector<ll>v[MAX];
//Stirling1 (n,k) = co-eff of x^k in x*(x+1)*(x+2)*....(x+n-1)
int Stirling1(int n, int r) {
    int nn = 1;
    while(nn < n) nn <<= 1;

    for(int i = 0; i < n; ++i) {v[i].push_back(i); v[i].push_back(1);}
    for(int i = n; i < nn; ++i) v[i].push_back(1);

    for(int j = nn; j > 1; j >>= 1) {
        int hn = j >> 1;
        for(int i = 0; i < hn; ++i) ntt.multiply(v[i], v[i + hn], v[i]);
    }
    return v[0][r];
}
NTT ntt(mod);
vector<ll>a,b,res;
//Stirling2 (n,k) = co-eff of x^k in product of polynomials A & B
//where A(i) = (-1)^i / i!  and B(i) = i^n / i!
int Stirling2(int n, int r) {
    a.resize(n+1); b.resize(n+1);
    for(int i = 0; i <= n; i++){
        a[i] = invfct[i];
        if(i % 2 == 1) a[i] = mod - a[i];
    }
    for(int i = 0; i <= n; i++){
        b[i] = bigMod(i, n, mod);
        b[i] = (b[i] * invfct[i]) % mod;
    }
    NTT ntt(mod);
    ntt.multiply(a,b,res);
    return res[r];
}
----------------------------------------------------------------------
//-----------NT and Cunting Ends---------
///---------------FFT
const int MAXN = (1<<18) + 500;
struct Complex{
    LD r,i;
    Complex(){r=0,i=0;}
    Complex(LD r ,LD i=0):r(r),i(i) {}
    Complex operator + (const Complex& t) const{
        return Complex(r+t.r,i+t.i) ;
    }
    Complex operator - (const Complex& t) const{
        return Complex(r-t.r,i-t.i);
    }
    Complex operator * (const Complex& t) const{
        return Complex(r*t.r-i*t.i,r*t.i+i*t.r);
    }
}A[MAXN],B[MAXN],C[MAXN];
void DFT(Complex y[],int n,int rev){
    for(int i=1,j,k,t; i<n; i++){
        for(j=0,k=n>>1,t=i; k; k>>=1,t>>=1) j=j<<1|t&1;
        if(i<j ) swap(y[i],y[j]);
    }
    for ( int s = 2 , ds = 1 ; s <= n ; ds = s , s <<= 1 ){
        Complex wn=Complex(cosl(rev*2*PI/s),sinl(rev*2*PI/s)),w=Complex(1,0),t;
        for(int k=0; k<ds; k++,w=w*wn){
            for(int i=k; i<n; i+=s){
                y[i+ds]=y[i]-(t=w*y[i+ds]);
                y[i]=y[i]+t;
            }
        }
    }
    if(rev==-1) for(int i=0; i<n; i++) y[i].r/=n;
}
void multiply(vector <int>&a,vector<int> &b,vector<int> &res){
    int N=1;
    int n = a.size();
    int m = b.size();
    while(N < n+m)N<<=1;
    a.resize(N);
    b.resize(N);
    res.resize(N);
    FOR(i,N)A[i] = Complex(),B[i] = Complex(),C[i] = Complex();
    for(int i=0;i<n;i++)A[i].r=a[i];
    for(int i=0;i<m;i++)B[i].r=b[i];
    DFT(A,N,1);
    DFT(B,N,1);
    for(int i=0;i<N;i++)C[i] = A[i]*B[i];
    DFT(C,N,-1);
    for(int i=0;i<N;i++)res[i] = (LL)(C[i].r+0.5);
    /// pop back zeros when doing multiple FFT
}
vi expoFFT(vi a,int p){
    vi ans(1);
    ans[0] = 1;
    while(p){
        if(p&1)ans=multiply(ans,a); // multiply will return result
        a=multiply(a,a);
        p>>=1;
    }
    return ans;
}
/// FFT (Slow,CP-Algorithm)
/// Must Define PI = acos(-1)
namespace FFT{
    typedef complex<double> cd;
    void fft(vector<cd> & a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i+j], v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) {
            for (cd & x : a)
                x /= n;
        }
    }
    vector<int> multiply(vector<int> const& a, vector<int> const& b) {
        vector<int> result;
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);
        result.resize(n);
        for (int i = 0; i < n; i++)
            result[i] = (fa[i].real()+0.5);
        return result;
    }
}
///----------------------------------NTT
int primitive_root(int p) {
    vector<int> factor;
    int phi = p-1,  n = phi;
    for (int i=2; i*i<=n; ++i)
        if (n%i == 0) {
            factor.push_back (i);
            while (n%i==0)  n/=i;
        }

    if (n>1)  factor.push_back(n);
    for (int res=2; res<=p; ++res) {
        bool ok = true;
        for (int i=0; i<factor.size() && ok; ++i)
            ok &= power(res, phi/factor[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
/// Call nttdata with mod to get required values
int nttdata(int mod, int &root, int &inv, int &pw) {
    int c = 0, n = mod-1;
    while (n%2 == 0) c++, n/=2;
    pw = (mod-1)/n;
    int g = primitive_root(mod);
    root = power(g, n, mod);
    inv = power(root, mod-2, mod);
    return c;
}
/// NTT starts
const int mod = 998244353;
struct NTT{
    int N;
    vector<int> perm;
    int mod, root, inv, pw;
    NTT(int mod, int root, int inv, int pw) :
        mod(mod), root(root), inv(inv), pw(pw) {}
    inline int mul(int a,int b){return ( a * 1LL * b )%mod;}
    inline int binPow(int a, int k){power}
    void precalculate() {
        perm.resize(N);
        perm[0] = 0;
        for (int k=1; k<N; k<<=1) {
            for (int i=0; i<k; i++) {
                perm[i] <<= 1;
                perm[i+k] = 1 + perm[i];
            }
        }
    }
    void fft(vector<int> &v, bool invert = false) {
        if (v.size() != perm.size()) {
            N = v.size();
            assert(N && (N&(N-1)) == 0);
            precalculate();
        }
        for (int i=0; i<N; i++)
            if (i < perm[i])
                swap(v[i], v[perm[i]]);

        for (int len = 2; len <= N; len <<= 1) {
            int factor = invert ? inv : root;
            for (int i = len; i < pw; i <<= 1)
                factor = (1LL * factor * factor) % mod;

            for (int i=0; i<N; i+=len) {
                int w = 1;
                for (int j=0; j<len/2; j++) {
                    int x = v[i+j], y = (1LL * w * v[i+j+len/2])%mod;
                    v[i+j] = (x+y)%mod;
                    v[i+j+len/2] = (x-y+mod)%mod;
                    w = (1LL * w * factor)%mod;
                }
            }
        }
        if (invert) {
            LL n1 = power(N, mod-2, mod);
            for (int &x : v) x=(1LL*x*n1)%mod;
        }
    }
    void multiply(vector<int>& a, vector<int> &b) {
        int n = 1;
        while (n < a.size()+ b.size())  n<<=1;
        a.resize(n);
        b.resize(n);

        fft(a);
        fft(b);
        for (int i=0; i<n; i++) a[i] = (1LL * a[i] * b[i])%mod;
        fft(a, true);
    }
    /// poly ^ p
    void bigMod(vector<int> &a,int p){
        fft(a,0);
        FOR(i,a.size())a[i] = binPow(a[i],p);
        fft(a,1);
    }
};