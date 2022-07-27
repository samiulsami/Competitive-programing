struct fastUpdate{
	///0 - indexed
	///O(1) update, O(sqrt(N)) query
	int arr[N];
	long long Blocks[K];

	void reset(){memset(Blocks,0,sizeof(Blocks));}

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
