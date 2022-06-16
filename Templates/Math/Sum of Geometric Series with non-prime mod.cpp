ll gsum(ll a, ll n){
    if(n==1)return a%mod;
    if(n%2==0){
        ll ans = gsum(a,n/2);
        return (ans+(ans*bigMod(a,n/2,mod))%mod)%mod;
    }
    return (a+(a*gsum(a,n-1))%mod)%mod;
}