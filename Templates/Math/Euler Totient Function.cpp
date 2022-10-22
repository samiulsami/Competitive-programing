ll getPhi(ll n){
    ll sqt=sqrt(n)+3;
    ll ret=n;

    if(n%2==0){
        while(n%2==0)n/=2;
        ret-=ret/2;
    }

    for(ll i=3; i<=sqt; i+=2){
        if(n%i==0){
            while(n%i==0)n/=i;
            ret-=ret/i;
        }
    }

    if(n>1)ret-=ret/n;
    return ret;
}