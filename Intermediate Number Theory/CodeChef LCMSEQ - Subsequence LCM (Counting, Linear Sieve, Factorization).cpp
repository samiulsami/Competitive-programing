#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

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

mint _pow2[10000005];
const int primesN = 1e7+5;
int spf[primesN]={0};
vector<int>primes;

void sieve(){///O(primesN)
	_pow2[0]=mint(1);
	_pow2[1]=mint(2);
	
	for(int i=2; i<primesN; i++){
		_pow2[i] = mint(2)*_pow2[i-1];
		if(spf[i]==0){
			spf[i]=i;
			primes.push_back(i);
		}
		for(int j=0; j<(int)primes.size() && primes[j]<=spf[i] && 1LL*i*primes[j]<primesN; j++)
			spf[i*primes[j]]=primes[j];
	}
}

vector<array<int,2> > primeFactorize(int x){///O(log(x))
    vector<array<int,2> > ret;
    while(x!=1){
        int curP=spf[x];
		ret.push_back(array<int,2>{curP,0});
        while(x%curP==0)x/=curP,ret.back()[1]++;    
    }
    return ret;
}

vector<int> factorize(int tmp){///~O(x^(1/3))
	vector<int>ret;
	while(tmp>1){
		int p = spf[tmp];
		int cnt = 0;
		int x=1;
		while(tmp%p==0){
			cnt++;
			tmp/=p;
		}
		int prevCount = int(ret.size());
		for(int j=0; j<cnt; j++){
			int curSize = int(ret.size());
			for(int k=0; k<prevCount; k++)
				ret.push_back(ret[curSize - prevCount + k]*p);
		}
		ret.push_back(p);
		for(int i=1; i<cnt; i++)
			ret.push_back(ret[int(ret.size())-1]*p);
	}
	return ret;
}

///M must divide all Si and Sj
int arr[N];
int freq[10000005]={0};
bool vis[10000007]={0};

int bruteforce(vector<int>a){
	int ret=0;
	for(int mask=0,mx=(1<<sz(a)); mask<mx; mask++){
		if(__builtin_popcount(mask)<2)continue;
		vector<int>tmp;
		for(int i=0; i<sz(a); i++){
			if(bool(mask&(1<<i)))tmp.push_back(a[i]);
		}
		
		bool valid=1;
		sort(all(tmp));
		int m = __builtin_popcount(mask);
		for(int i=0; valid && i<sz(tmp); i++){
			for(int j=i+1; j<sz(tmp); j++){
				int x = (1LL*m*tmp[i])/__gcd(m,tmp[i]);
				int y = (1LL*m*tmp[j])/__gcd(m,tmp[j]);
				if((tmp[j]-tmp[i])!=(y-x)){
					valid=0;
					break;
				}
			}
		}
		
		if(valid){
			//for(int i:tmp)printf("%d ",i);
			//printf("\n");
			ret++;
		}
	}
	
	return ret;
	
}
/*
2
5 
6 2 21 2 1
10
2 4 6 8 32 16 16 2 3 3
*/


inline void solve(int caseNum){
	int n;
	scanf("%d",&n);
	vector<int>toClear;
	map<int,int>mp;
	vector<int>bv;
	
	for(int i=0; i<n; i++){
		scanf("%d",&arr[i]);
		mp[arr[i]]++;
		bv.push_back(arr[i]);
	}
	
	mint ans(0);
	for(auto it:mp){
		vector<int>divisors = factorize(it.first);
		
		ans += _pow2[it.second] - mint(it.second) - mint(1);
		for(int x:divisors){
			if(x>1)ans -=  C.ncr(it.second,x);
			if(!vis[x]){
				vis[x]=1;
				toClear.push_back(x);
			}
			freq[x]+=it.second;
		}
		
		
	}
	
	for(int i:toClear){
		ans += C.ncr(freq[i],i);
		vis[i]=0;
		freq[i]=0;
	}
	

	//printf("ans: %d %d\n",ans,bruteforce(bv));
	printf("%d\n",ans.val);
}

int main(){
	primes.reserve(10000004);
	sieve();

  // ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	scanf("%d",&T);
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}