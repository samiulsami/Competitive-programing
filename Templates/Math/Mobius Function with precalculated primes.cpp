int mobius[primesN];
void mobius_init(){
	///mobius[1] = 1;
	///mobius[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mobius[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=1; i<primesN; i++)mobius[i]=1;
	for(int p:primes){
		if(1LL*p*p>=primesN)break;
		int x = p*p;
		for(int j=x; j<primesN; j+=x)mobius[j]=0;
	}
	for(int p:primes)
		for(int j=p; j<primesN; j+=p)mobius[j] *= -1;
}