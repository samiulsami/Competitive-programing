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