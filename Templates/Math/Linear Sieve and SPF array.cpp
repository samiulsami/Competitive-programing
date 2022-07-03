const int primesN = 1e7+5;
int spf[primesN]={0};
vector<int>primes;

void sieve(){///O(primesN)
	for(int i=2; i<primesN; i++){
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