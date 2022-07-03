int mu[primesN];
inline void mobius(){
	///mu[1] = 1;
	///mu[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mu[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=0; i<primesN; i++)mu[i]=2;
	mu[1]=1;
	for(int i=2; i<primesN; i++){
		if(mu[i]==2){
			mu[i]=-1;
			if(i<=primesN/i){
				int x=i*i;
				for(int j=x; j<primesN; j+=x)mu[j]=0;
			}
			for(int j=i+i; j<primesN; j+=i){
				if(mu[j]==2)mu[j]=-1;
				else mu[j]*=-1;
			}
		}
	}
}