const int primesN = 1e6+5;
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