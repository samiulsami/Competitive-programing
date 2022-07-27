struct fastQuery{
	///0 - indexed
	///O(sqrt(N)) update, O(1) query
	int arr[N];
	long long Blocks[K];
	long long pref[K][K];
	int n;

	void init(int len){
		n=len;	
		for(int i=0; i<K; i++)Blocks[i]=0;
		for(int i=0,d,r; i<len; i++){
			d=i/K,r=i%K;
			pref[d][r]=arr[i];
			if(r)pref[d][r] += pref[d][r-1];
		}
		updateBlocks(0);
	}

	void set(int pos, int val){
		arr[pos]=val;
		int cur=pos/K;
		int l=pos%K,r=K-1;
		if(r==(n/K))r=n%K;
		for(;l<=r;l++){
			pref[cur][l]=arr[pos++];
			if(l)pref[cur][l] += pref[cur][l-1];
		}
		updateBlocks(cur);
	}

	long long query(int l){
		int _l = (l/K);
		long long ret=0;
		if(l>0)ret = Blocks[_l-1];
		return ret + pref[_l][l%K];
	}

	long long query(int l, int r){
		long long ret = query(r);
		if(l>0)ret -= query(l-1);
		return ret;
	}
	
	void updateBlocks(int BlockNum){
		for(int i=BlockNum,lastBlock=n/K; i<K; i++){
			if(i==lastBlock)Blocks[i] = pref[i][n%K];
			else Blocks[i] = pref[i][K-1];
			if(i)Blocks[i] += Blocks[i-1];
		}
	}
}sq;
