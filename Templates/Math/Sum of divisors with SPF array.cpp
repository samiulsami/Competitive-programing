ll SOD(int x){
    ll ret=1;
    while(x!=1){
        int curP=spf[x];
        ll pPower=curP;
        while(x%curP==0){
            x/=curP;
            pPower*=curP;
        }
        ret = ret*(ll(pPower-1)/ll(curP-1));
    }
    return ret;
}