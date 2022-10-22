///sgtlaugh's PCF https://github.com/sgtlaugh/algovault/blob/master/code_library/fast_prime_counting.cpp
///Works for integers up to ~1e12
///CALL gen() FIRST

namespace pcf{
	const int MAXV = 20000010;
	const int MAXP = 7;
	const int MAXN = 50;
	const int MAXM = 2 * 3 * 7 * 5 * 11 * 13 * 17; /// Product of the first MAXP primes

	constexpr auto fast_div = [](const long long& a, const int& b) ->long long {return double(a) / b + 1e-9;};
	int prod[MAXP], pi[MAXV], dp[MAXN][MAXM];
	 
	uint32_t status[(MAXV>>6)+2];
	inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
	inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
	vector<int>primes;
	 
	 void sieve(){
	    uint32_t sq=sqrt(MAXV)+5;
	    pi[0]=pi[1]=0;pi[2]=1;pi[3]=2;
	    primes.push_back(2);primes.push_back(3);
	    for(uint32_t i=3; i<=sq; i+=2)
	         if(!checkP(i))
	         	for(uint32_t j=i*i,inc=(i<<1); j<MAXV; j+=inc)setP(j);   
	    for(uint32_t i=5; i<MAXV; i+=2){	
	    	pi[i] = pi[i-1] = pi[i-2];
	    	if(!checkP(i))primes.push_back(i),pi[i]++;
	    }
	}
	 
	void gen(){
	    int i, j;
	    assert(MAXN >= MAXP);

	    sieve();
	    for (prod[0] = primes[0], i = 1; i < MAXP; i++){
	        prod[i] = prod[i - 1] * primes[i];
	    }

	    for (i = 0; i < MAXM; i++) dp[0][i] = i;
	    for (i = 1; i < MAXN; i++){
	        for (j = 1; j < MAXM; j++){
	            dp[i][j] = dp[i - 1][j] - dp[i - 1][fast_div(j, primes[i - 1])];
	        }
	    }
	}

	uint64_t phi(long long m, int n){
	    if (!n) return m;
	    if (n < MAXN && m < MAXM) return dp[n][m];
	    if (n < MAXP) return dp[n][m % prod[n - 1]] + fast_div(m, prod[n - 1]) * dp[n][prod[n - 1]];

	    long long p = primes[n - 1];
	    if (m < MAXV && p * p >= m) return pi[m] - n + 1;
	    if (p * p * p < m || m >= MAXV) return phi(m, n - 1) - phi(fast_div(m, p), n - 1);

	    int lim = pi[(int)sqrt(0.5 + m)];
	    uint64_t res = pi[m] - (lim + n - 2) * (lim - n + 1) / 2;
	    for (int i = n; i < lim; i++){
	        res += pi[fast_div(m, primes[i])];
	    }

	    return res;
	}

	uint64_t lehmer(long long n){
	    if (n < MAXV) return pi[n];

	    int s = sqrt(0.5 + n), c = cbrt(0.5 + n);
	    uint64_t res = phi(n, pi[c]) + pi[c] - 1;
	    for (int i = pi[c]; i < pi[s]; i++){
	        res -= lehmer(fast_div(n, primes[i])) - i;
	    }

	    return res;
	}

} 