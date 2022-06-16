///Binomial Coefficient, nCr, O(min(n,r))
ll nCr(int n, int r){
    if(r==0)return 1;
    ll ret=1;
    if(r>n-r)r=n-r;
    for(ll i=0; i<r; i++){
        ret*=(n-i);
        ret/=(i+1);
    }
    return ret;
}