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