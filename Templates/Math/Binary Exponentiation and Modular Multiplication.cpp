///(a^b)%MOD
const int MOD = 1e9+7;

int bigmod(int a, int b){
    if(b==0)return 1;
    if(b==1)return a%MOD;
    int ret=1;
    a%=MOD;
    while(b>0){
        if(b&1)ret=(1LL*ret*a)%MOD;
        b>>=1;
        a=(1LL*a*a)%MOD;
    }
    return ret%MOD;
}

///(a*b)%MOD
int modmul(int a, int b){
	if(b==0)return 0;
	if(b==1)return a%MOD;
    int ret=0;
    a%=MOD;
    while(b>0){
        if(b&1)ret=(1LL*ret+1LL*a)%MOD;
        b>>=1;
        a=((1LL*a)<<1LL)%MOD;
    }
    return ret%MOD;
}

