template<typename T>
struct brentPollardRho{///https://cp-algorithms.com/algebra/factorization.html#brents-algorithm
	int primes[121]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,
	223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,
	409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659};
	
	T modpow(T a, T b, T MOD){
	    if(b==0)return 1;
	    if(b==1)return a%MOD;
	    T ret=1;
	    a%=MOD;
	    while(b>0){
	        if(b&1)ret=(ret*a)%MOD;
	        b>>=1;
	        a=(a*a)%MOD;
	    }
	    return ret%MOD;
	}

	T modmul(T a, T b, T MOD){
		if(b==0)return 0;
		if(b==1)return a%MOD;
	    T ret=0;
	    a%=MOD;
	    while(b>0){
	        if(b&1)ret=(ret+a)%MOD;
	        b>>=1;
	        a=(a<<1)%MOD;
	    }
	    return ret%MOD;
	}

	inline T f(T x, T c, T mod){return (modmul(x, x, mod) + c) % mod;}
	inline T abs(T a, T b){
		return a>b ? a-b:b-a;
	}

	bool isPrime(T n, int iter=7) {
		///kactl MillerRabin
		///Guaranteed to work for integers up to 7e18
		if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
		uint64_t A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
		    s = __builtin_ctzll(n-1), d = n >> s;
		auto check = [&](uint64_t a)->bool{
			uint64_t p = modpow(a%n, d, n), i = s;
			while (p != 1 && p != n - 1 && a % n && i--)
				p = modmul(p, p, n);
			if (p != n-1 && i != s) return 1;
			return 0;
		};
		for (uint64_t a : A)
			if(check(a))return 0;
		if(n<=ll(7e18))return 1;
		while(iter--){
			uint64_t a = 2 + rng()%(n - 3);
			if(check(a))return 0;
		}
		return 1;
	}

	T mygcd(T a, T b){return a%b?mygcd(b,a%b):b;}
	T abs(T a){return a<0?-a:a;}

	T brent(T n, T x0=2, T c=1) {
	    T x = x0;
	    T g = 1;
	    T q = 1;
	    T xs, y;

	    int m = 128;
	    int l = 1;
	    while (g == 1) {
	        y = x;
	        for (int i = 1; i < l; i++)
	            x = f(x, c, n);
	        int k = 0;
	        while (k < l && g == 1) {
	            xs = x;
	            for (int i = 0; i < m && i < l - k; i++) {
	                x = f(x, c, n);
	                q = modmul(q, abs(y - x), n);
	            }
	            g = mygcd(q, n);
	            k += m;
	        }
	        l *= 2;
	    }
	    if (g == n) {
	        do {
	            xs = f(xs, c, n);
	            g = mygcd(abs(xs - y), n);
	        } while (g == 1);
	    }
	    return g;
	}

	vector<pair<T,int> >factorize(T n){
		vector<pair<T,int> >ret;
		for(int i=0; i<100; i++){
			if(n%primes[i]==0){
				ret.push_back({(T)primes[i],0});
				while(n%primes[i]==0){
					n/=primes[i];
					ret.back().second++;
				}
			}
		}

		while(n>1){
			if(isPrime(n)){
				ret.push_back({n,1});
				break;
			}
			T fact = brent(n);
			ret.push_back({fact,0});
			while(n%fact==0){
				n/=fact;
				ret.back().second++;
			}
		}

		return ret;
	}
};

brentPollardRho<__int128>bpr;