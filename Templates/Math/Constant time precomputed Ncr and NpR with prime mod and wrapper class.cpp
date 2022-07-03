const int MOD = 1e9+7;

struct mint{
	///credits: https://codeforces.com/blog/entry/63903
	int val;
	mint(long long v = 0){ val = v%MOD; if(val<0)val+=MOD;}
	mint(long long a, long long b):val(0){ *this += a; *this /= b;}
	mint& operator+=(mint const &b){val+=b.val; if(val>=MOD)val-=MOD; return *this;}
	mint& operator-=(mint const &b){val-=b.val; if(val<0)val+=MOD; return *this;}
	mint& operator*=(mint const &b){val=(1LL*val*b.val)%MOD; return *this;}
	friend mint bigmod(mint a, long long b){mint ret = 1;while(b){if(b&1)ret *= a;a*=a;b>>=1;}return ret;}
	friend mint inverse(mint a){return bigmod(a,MOD-2);}
	mint& operator/=(mint const& b){return *this *= inverse(b); }
	friend mint operator+(mint a, mint const b){return a += b;}
	friend mint operator-(mint a, mint const b){return a -= b; }
	friend mint operator-(mint const a){return 0-a; }
	friend mint operator*(mint a, mint const b){return a *= b;}
	friend mint operator/(mint a, mint const b){return a /= b;}
	friend std::ostream& operator<<(std::ostream& os, mint const& a){return os << a.val;}
	friend std::istream& operator>>(std::istream& is, mint &a){long long x;is>>x;a = mint(x);return is;}
	friend bool operator==(mint const& a, mint const& b){return a.val == b.val;}
	friend bool operator!=(mint const& a, mint const& b){return a.val != b.val;}
};

struct PNC{
	static const int pncSZ=1e7+5;
	mint fact[pncSZ],factInv[pncSZ];
	PNC(){
		fact[0]=mint(1);
		for(int i=1; i<pncSZ; i++)fact[i]=fact[i-1]*mint(i);
		factInv[pncSZ-1]=mint(1)/fact[pncSZ-1];
		for(int i=pncSZ-1; i>0; i--)factInv[i-1]=mint(i)*factInv[i];
	}
	inline mint ncr(int n, int r){
		if(n<r)return 0;
		return fact[n]*factInv[r]*factInv[n-r];
	}
	inline mint npr(int n, int r){
		if(n<r)return 0;
		return fact[n]*factInv[n-r];
	}
}C;