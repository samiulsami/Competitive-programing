int catalan_number(int n){
    int ret=nCr(2*n,n);
    return ret/(n+1);
}