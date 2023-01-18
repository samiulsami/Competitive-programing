#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int primesN = 31699999;
uint32_t status[(primesN>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;

void sieve(){
    uint32_t sq=sqrt(primesN)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<primesN; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<primesN; i+=2)if(!checkP(i))primes.push_back(i);
}

vector<ll>dprimes;

vector<int> factorize(ll x){
	vector<int>ret;
	for(ll a:dprimes){
		if(x%a==0){
			ret.push_back(0);
			while(x%a==0)x/=a,ret.back()++;
		}
	}
	return ret;
}

///MOD must be less than 1073741824
///MOD must be prime for division to work
template<const int32_t MOD = 0>
struct ModInt{
	///based on https://codeforces.com/blog/entry/63903
	int32_t val;
	ModInt(int64_t v = 0){ val = v%MOD; if(val<0)val+=MOD;}
	ModInt(int64_t a, int64_t b):val(0){ *this += a; *this /= b;}
	ModInt& operator+=(ModInt const &b){val+=b.val; if(val>=MOD)val-=MOD; return *this;}
	ModInt& operator-=(ModInt const &b){val-=b.val; if(val<0)val+=MOD; return *this;}
	ModInt& operator*=(ModInt const &b){val=(1LL*val*b.val)%MOD; return *this;}
	ModInt& operator++(){val++; if(val>=MOD)val-=MOD; return *this;}
	ModInt& operator--(){val--; if(val<0)val+=MOD; return *this;}
	friend ModInt bigmod(ModInt a, int32_t b){ModInt ret = 1;while(b){if(b&1)ret *= a;a*=a;b>>=1;}return ret;}
	friend ModInt inverse(ModInt a){return bigmod(a,MOD-2);}
	ModInt& operator/=(ModInt const& b){return *this *= inverse(b);}
	friend ModInt operator+(ModInt a, ModInt const b){return a += b;}
	friend ModInt operator-(ModInt a, ModInt const b){return a -= b;}
	friend ModInt operator-(ModInt const a){return 0-a;}
	friend ModInt operator*(ModInt a, ModInt const b){return a *= b;}
	friend ModInt operator/(ModInt a, ModInt const b){return a /= b;}
	friend std::ostream& operator<<(std::ostream& os, ModInt const& a){return os << a.val;}
	friend std::istream& operator>>(std::istream& is, ModInt &a){int64_t x;is>>x;a = ModInt(x);return is;}
	friend bool operator==(ModInt const& a, ModInt const& b){return a.val == b.val;}
	friend bool operator!=(ModInt const& a, ModInt const& b){return a.val != b.val;}
	bool operator<(ModInt const& a){return val<a.val;}
	bool operator<=(ModInt const& a){return val<=a.val;}
	bool operator>(ModInt const& a){return val>a.val;}
	bool operator>=(ModInt const& a){return val>=a.val;}
};

const int MOD = 998244353;
using mint = ModInt<MOD>;

mint fact[70];
mint ifact[70];

inline void solve(int caseNum){
	ll D;
	cin>>D;
	for(int i:primes){
		if(1LL*i*i>D)break;
		if(D%i==0){
			while(D%i==0)D/=i;
			dprimes.push_back(i);
		}
	}

	if(D>1)dprimes.push_back(D);

	fact[0] = 1;
	for(int i=1; i<70; i++)fact[i] = mint(i)*fact[i-1];
	ifact[69] = bigmod(fact[69],MOD-2);
	for(int i=68; i>=0; i--)ifact[i] = mint(i+1)*ifact[i+1];

	int q;
	cin>>q;

	while(q--){
		ll u,v;
		cin>>u>>v;

		int pos=0,neg=0;

		mint ans(1);
		for(ll x:dprimes){
			int diff=0;
			while(u%x==0)diff++,u/=x;
			while(v%x==0)diff--,v/=x;
			if(diff>0)pos+=diff;
			else neg-=diff;
			ans *= ifact[abs(diff)];
		}

		ans *= fact[pos];
		ans *= fact[neg];
		cout<<ans<<"\n";
	}
}	

int main(){

	sieve();
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}