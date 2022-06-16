///GCD theory stuff

///Sum of co-prime numbers of n = n*(phi(n)/2)
///if 'd' is a divisor of n, then there are phi(n/d) numbers i<=n for which gcd(i,n)==d

///Sum of gcd(i,n) for i=1 to n-1
//LCM(1,n) + LCM(2,n) + ... + LCM(n,n) = (n/2)*[summation i:0 to k](phi[d[i]] * d[i]) + n/2 
//https://forthright48.com/spoj-lcmsum-lcm-sum