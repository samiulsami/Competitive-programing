const int K = 150;///Block size
const int L = (N+K-1)/K;///Number of blocks

struct fastUpdate{
	///0 - indexed
	///O(1) update, O(L+K+K) query
	int arr[N];
	long long Blocks[L];

	void reset(int n){for(int i=0,x=n/K; i<=x; i++)Blocks[i]=0;}

	inline void set(int pos, int val){
		Blocks[pos/K]+=val;
		arr[pos]=val;
	}

	long long query(int l, int r){
		int _l = l/K, _r = r/K;
		long long ret=0;
		if(_l==_r){
			for(;l<=r;l++)ret+=arr[l];
			return ret;
		}
		for(int i=l,mx=(_l+1)*K; i<mx; i++)
			ret += arr[i];
		for(int i=_l+1; i<_r; i++)
			ret += Blocks[i];
		for(int i=(_r*K); i<=r; i++)
			ret +=arr[i];
		return ret;
	}
}sq;