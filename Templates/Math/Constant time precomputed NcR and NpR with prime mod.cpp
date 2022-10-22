///nPr and nCr O(1) per query, O(n) precomputation
///MOD must be prime

struct PNC{
	static const int pncSZ=2e5+5;
	static const int MOD=998244353;
	
	int fact[pncSZ],factInv[pncSZ];
	PNC(){
		fact[0]=1;
		for(int i=1; i<pncSZ; i++)fact[i]=(1LL*fact[i-1]*i)%MOD;
		factInv[pncSZ-1]=bigMOD(fact[pncSZ-1], MOD-2);
		for(int i=pncSZ-1; i>0; i--)factInv[i-1]=(1LL*i*factInv[i])%MOD;
	}
	int bigMOD(int a, int b){
		if(a==0)return 0;
		int ret=1;
		while(b>0){
			if(b&1)ret=(1LL*ret*a)%MOD;
			b>>=1;
			a=(1LL*a*a)%MOD;
		}
		return ret%MOD;
	}
	inline int ncr(int n, int r){
		if(n<r)return 0;
		return ((1LL*fact[n]*factInv[r])%MOD * 1LL*factInv[n-r])%MOD;
	}
	inline int npr(int n, int r){
		if(n<r)return 0;
		return (1LL*fact[n]*factInv[n-r])%MOD;
	}
}C;