#include<bits/stdc++.h>
using namespace std;

const int primesN=1e7+5;
int mobius[primesN];
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

void mobius_init(){
	for(int i=1; i<primesN; i++)mobius[i]=1;
	for(int p:primes){
		if(1LL*p*p>=primesN)break;
		int x = p*p;
		for(int j=x; j<primesN; j+=x)mobius[j]=0;
	}
	for(int p:primes)
		for(int j=p; j<primesN; j+=p)mobius[j] *= -1;
}


int main(){
	sieve();
	mobius_init();
	int t;
	scanf("%d",&t);
	while(t--){
		long long n;
		scanf("%lld",&n);
		long long ans=n;
		for(long long i=2; i*i<=n; i++)ans += 1LL*mobius[i]*(n/(i*i));	
		printf("%lld\n",ans);
	}
return 0;
}