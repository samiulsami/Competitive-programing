///sgtlaugh's PCF https://codeforces.com/blog/entry/91632?#comment-802278
///Works for integers up to ~1e12
///CALL gen() FIRST

namespace pcf{
	#define MAXN 100
	#define MAXM 100010
	#define MAXP 10000010
	 
	int prime_cnt[MAXP];
	long long dp[MAXN][MAXM];
	 
	uint32_t status[(MAXP>>6)+2];
	inline bool checkP(uint32_t i){return (status[(i>>6)]&(1<<((i>>1)&31)));}
	inline void setP(uint32_t i){ status[i>>6]|=(1<<((i>>1)&31));}
	vector<int>primes;
	 
	 void sieve(){
	    uint32_t sq=sqrt(MAXP)+5;
	    prime_cnt[0]=prime_cnt[1]=0;prime_cnt[2]=1;prime_cnt[3]=2;
	    primes.push_back(2);primes.push_back(3);
	    for(uint32_t i=3; i<=sq; i+=2)
	         if(!checkP(i))
	         	for(uint32_t j=i*i,inc=(i<<1); j<MAXP; j+=inc)setP(j);   
	    for(uint32_t i=5; i<MAXP; i+=2){	
	    	prime_cnt[i] = prime_cnt[i-1] = prime_cnt[i-2];
	    	if(!checkP(i))primes.push_back(i),prime_cnt[i]++;
	    }
	}
	 
	void gen(){///CALL FIRST
	    sieve();
	    for (int m = 0; m < MAXM; m++) dp[0][m] = m;
	    for (int n = 1; n < MAXN; n++){
	        for (int m = 0; m < MAXM; m++){
	            dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
	        }
	    }
	}
	 
	long long phi(long long m, int n){
	    if (n == 0) return m;
	    if (m < MAXM && n < MAXN) return dp[n][m];
	    if ((long long)primes[n - 1] * primes[n - 1] >= m && m < MAXP) return prime_cnt[m] - n + 1;
	 
	    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
	}
	
	///Returns the number of primes <= m
	long long lehmer(long long m){///~O(m^(2/3))
	    if (m < MAXP) return prime_cnt[m];
	 
	    int s = sqrt(0.5 + m), y = cbrt(0.5 + m);
	    int a = prime_cnt[y];
	 
	    long long res = phi(m, a) + a - 1;
	    for (int i = a; primes[i] <= s; i++){
	        res = res - lehmer(m / primes[i]) + lehmer(primes[i]) - 1;
	    }
	    return res;
	}
} 