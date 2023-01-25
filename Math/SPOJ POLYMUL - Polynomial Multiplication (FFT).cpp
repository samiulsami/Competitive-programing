#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

/// FFT (Slow,CP-Algorithm)
/// Must Define PI = acos(-1)
const double PI = acos(-1);
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
    vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
        vector<ll> result;
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
            result[i] = (fa[i].real()+0.5L);
        return result;
    }
}



inline void solve(int caseNum){
	int n;
	cin>>n;

	vector<ll>a(n+1),b(n+1);
	for(int i=0; i<=n; i++)cin>>a[i];
	for(int j=0; j<=n; j++)cin>>b[j];

	auto ans = FFT::multiply(a,b);
	
	for(int i=0,x=2*n+1; i<x; i++)cout<<ans[i]<<" ";
	cout<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}