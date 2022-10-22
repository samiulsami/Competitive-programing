///Generates prime numbers from [1,n] in O(nloglogn)
const int N=1e6+5;
uint32_t status[(N>>6)+2];
inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
vector<int>primes;

void sieve(){
    uint32_t sq=sqrt(N)+5;
    for(uint32_t i=3; i<=sq; i+=2)
        if(!checkP(i))
            for(uint32_t j=i*i,inc=(i<<1); j<N; j+=inc)
                setP(j);
    primes.push_back(2);
    for(uint32_t i=3; i<N; i+=2)if(!checkP(i))primes.push_back(i);
}

vector<pair<long long, int> > factorize(long long x){
	vector<pair<long long, int> > ret;
	for(int i:primes){
		if(1LL*i*i>=N)break;
		if(x%i==0){
			ret.push_back({i,0});
			while(x%i==0){
				x/=i;
				ret.back().second++;
			}
		}
	}
	if(x>1)ret.push_back({x,1});
	return ret;
}

void mobius_init(){
	///mobius[1] = 1;
	///mobius[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mobius[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=1; i<N; i++)mobius[i]=1;
	for(int p:primes){
		if(1LL*p*p>=N)break;
		int x = p*p;
		for(int j=x; j<N; j+=x)mobius[j]=0;
	}
	for(int p:primes)
		for(int j=p; j<N; j+=p)mobius[j] *= -1;
}

///standalone mobius
int mu[N];
inline void mobius(){
	///mu[1] = 1;
	///mu[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mu[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=0; i<N; i++)mu[i]=2;
	mu[1]=1;
	for(int i=2; i<N; i++){
		if(mu[i]==2){
			mu[i]=-1;
			if(i<=N/i){
				int x=i*i;
				for(int j=x; j<N; j+=x)mu[j]=0;
			}
			for(int j=i+i; j<N; j+=i){
				if(mu[j]==2)mu[j]=-1;
				else mu[j]*=-1;
			}
		}
	}
}

///Generates primes from 1 to primesN in O(n)
///spf stores the smalles prime factor for each numberconst int primesN=1e5+5;
typedef pair<int,int> pii;

const int N=1e5+5;
int spf[N]={0};
vector<int>primes;

void sieve(){
	for(int i=2; i<N; i++){
		if(spf[i]==0){
			spf[i]=i;
			primes.push_back(i);
		}
		for(int j=0; j<(int)primes.size() && primes[j]<=spf[i] && 1LL*i*primes[j]<primesN; j++)
			spf[i*primes[j]]=primes[j];
	}
}

vector<array<int,2> > factorize(int x){
    vector<array<int,2> > ret;
    while(x!=1){
        int curP=spf[x];
		ret.push_back(array<int,2>{curP,0});
        while(x%curP==0)x/=curP,ret.back()[1]++;    
    }
    return ret;
}

///Factorize factorials
vector<pii> factorize(int x){
    vector<pii> ret;
    for(int p:primes){
        if(p>x)break;
        int n=x,freq=0;
        while(n/p>0){
            freq+=n/p;
            n/=p;
        }
        if(freq>0)ret.push_back(pii(p,freq));
    }
    return ret;
}

///Sum of divisors O(logn)
ll SOD(int x){
    ll ret=1;
    while(x!=1){
        int curP=spf[x];
        ll pPower=curP;
        while(x%curP==0){
            x/=curP;
            pPower*=curP;
        }
        ret = ret*(ll(pPower-1)/ll(curP-1));
    }
    return ret;
}

///Fast GCD

int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}
///Calculates the value of phi for all numbers from [1,n] in O(nloglogn)
const int phiMX=1e3;
int phi[phiMX];

void precalc_phi(int n){
    for(int i=0; i<=n; i++)phi[i]=i;
    for(int i=2; i<=n; i++){
        if(phi[i]==i){
            for(int j=i; j<=n; j+=i)
                phi[j]-=phi[j]/i;
        }
    }
}

///Calculates phi(n) in O(sqrt(n))
int getPhi(int n){
    int sqt=sqrt(n)+3;
    int ret=n;

    if(n%2==0){
        while(n%2==0)n/=2;
        ret-=ret/2;
    }

    for(int i=3; i<=sqt; i+=2){
        if(n%i==0){
            while(n%i==0)n/=i;
            ret-=ret/i;
            sqt=sqrt(n)+2;
        }
    }

    if(n>1)ret-=ret/n;
    return ret;
}

///(a*b)%mod
ll modMul(ll a, ll b, ll mod){
    ll ret=0;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret+a)%mod;
        b>>=1;
        a=(a<<1)%mod;
    }
    return ret%mod;
}
///(a^b)%mod
ll bigMod(ll a, ll b, ll mod){
    if(a==0)return 0;
    ll ret=1;
    a%=mod;
    while(b>0){
        if(b&1)ret=(ret*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ret%mod;
}

///-----------------------------------------------------------------------


///-----------------------------------------------------------------------
///Binomial Coefficient, nCr, O(min(n,r))
ll nCr(int n, int r){
    if(r==0)return 1;
    ll ret=1;
    if(r>n-r)r=n-r;
    for(ll i=0; i<r; i++){
        ret*=(n-i);
        ret/=(i+1);
    }
    return ret;
}

///-----------------------------------------------------------------------
///nPr and nCr O(1) per query, O(n) precomputation
///MOD must be prime

struct PNC{
	static const int pncSZ=2e5+5;
	static const int MOD=998244353;
	
	int fact[pncSZ],factInv[pncSZ];
	PNC(){
		fact[0]=1;
		for(int i=1; i<pncSZ; i++)fact[i]=(1LL*fact[i-1]*i)%MOD;
		factInv[pncSZ-1]=bigMOD(fact[pncSZ-1], MOD-2);
		for(int i=pncSZ-1; i>0; i--)factInv[i-1]=(1LL*i*factInv[i])%MOD;
	}
	int bigMOD(int a, int b){
		if(a==0)return 0;
		int ret=1;
		while(b>0){
			if(b&1)ret=(1LL*ret*a)%MOD;
			b>>=1;
			a=(1LL*a*a)%MOD;
		}
		return ret%MOD;
	}
	inline int ncr(int n, int r){
		if(n<r)return 0;
		return ((1LL*fact[n]*factInv[r])%MOD * 1LL*factInv[n-r])%MOD;
	}
	inline int npr(int n, int r){
		if(n<r)return 0;
		return (1LL*fact[n]*factInv[n-r])%MOD;
	}
}C;


///-----------------------------------------------------------------------

int catalan_number(int n){
    int ret=nCr(2*n,n);
    return ret/(n+1);
}

///-----------------------------------------------------------------------
///K'th root of a number. value of eps affects accuracy and speed
const double eps = 1e-9;
double kthRoot(double x, double k){
    double low=1,high=x;
    double mid = (low+high)/(double)2;
    while(abs((pow(mid,k))-x)>=eps){
        if(pow(mid,k)>x)high=mid;
        else low=mid;
        mid=(low+high)/(double)2;
    }
    return mid+eps;
}
///-------------------------------------------------------------

///GCD theory stuff

///Sum of co-prime numbers of n = n*(phi(n)/2)
///if 'd' is a divisor of n, then there are phi(n/d) numbers i<=n for which gcd(i,n)==d

///Sum of gcd(i,n) for i=1 to n-1
//LCM(1,n) + LCM(2,n) + ... + LCM(n,n) = (n/2)*[summation i:0 to k](phi[d[i]] * d[i]) + n/2 
//https://forthright48.com/spoj-lcmsum-lcm-sum

for(int i=1; i<n; i++){
    for(int j=i+i; j<=n; j++){
        gcdSum[j]+=(i*phi[j/i]);
    }
}

///Sum of geometric series with modulo
ll gsum(ll a, ll n){
    if(n==1)return a%mod;
    if(n%2==0){
        ll ans = gsum(a,n/2);
        return (ans+(ans*bigMod(a,n/2,mod))%mod)%mod;
    }
    return (a+(a*gsum(a,n-1))%mod)%mod;
}
///
///-----------------------------------------------------------------------

ll lcm(ll a, ll b ){return ((a/__gcd(a,b))*b);}

