///mobius[1] = 1;
///mobius[x] = 0 if x is divisible by a^2 where 'a' is a prime
///mobius[x] = (-1)^k if 'x' is the product of 'k' distinct primes

int mobius(int x){
	if(x==1)return 1;
	int ret = 1;
	
	for(int p:primes){
		if(1LL*p*p>x)break;
		if(x%p==0){
			x/=p;
			ret = -ret;
			if(x%p==0)return 0;
		}
	}
	
	if(x>1)ret = - ret;
	return ret;
}