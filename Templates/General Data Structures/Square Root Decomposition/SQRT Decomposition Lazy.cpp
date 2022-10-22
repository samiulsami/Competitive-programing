const int K = 450;///Block size
const int L = (N+K-1)/K;///Number of blocks

struct SQRTLazy{///cses 1735
	///0 - indexed
	///O(L+K+K) update, O(L+K+K) query
	long long arr[N];
	long long Blocks[L];
	//long long Lazy[L];
	long long add[L];
	long long set[L];
	int n;

	void reset(int _n){
		n=_n;
		for(int i=0,x=_n/K; i<=x; i++){
			Blocks[i]=0;
			set[i]=0;	
			add[i]=0;
		}
	}

	inline void push_lazy(int b){
		int l = b*K;
		int r = min(n,(b+1)*K);
		if(set[b]){
			for(int i=l; i<r; i++)arr[i]=set[b];
			set[b]=0;
		}

		if(add[b]){
			for(int i=l; i<r; i++)arr[i]+=add[b];
			add[b]=0;
		}

	}

	void update(int l, int r, ll x, bool _type){///1 = set, 0 = add
		int _l = l/K, _r = r/K;

		if(_l==_r){
			push_lazy(_l);
			for(int i=l; i<=r; i++){
				if(_type){
					Blocks[_l] += x-arr[i];
					arr[i] = x;
				}
				else {
					arr[i] += x;
					Blocks[_l] += x;
				}
			}
			return;
		}

		push_lazy(_l);
		for(int i=l,mx=(_l+1)*K; i<mx; i++){
			if(_type){
				Blocks[_l] += x-arr[i];
				arr[i] = x;
			}
			else {
				arr[i] += x;
				Blocks[_l] += x;
			}
		}

		for(int i=_l+1; i<_r; i++){
			if(_type){
				Blocks[i] = (1LL*K*x);
				set[i] = x;
				add[i] = 0;
			}
			else{
				Blocks[i] += (1LL*K*x);
				if(set[i])set[i] += x;
				else add[i] += x;
			}
		}

		push_lazy(_r);
		for(int i=(_r*K); i<=r; i++){
			if(_type){
				Blocks[_r] += x-arr[i];
				arr[i] = x;
			}
			else {
				arr[i] += x;
				Blocks[_r] += x;
			}
		}
	}

	long long query(int l, int r){
		int _l = l/K, _r = r/K;
		long long ret=0;

		if(_l==_r){
			push_lazy(_l);
			for(;l<=r;l++){
				ret+=arr[l];
			}
			return ret;
		}

		push_lazy(_l);
		for(int i=l,mx=(_l+1)*K; i<mx; i++){
			ret += arr[i];
		}

		for(int i=_l+1; i<_r; i++){
			ret += Blocks[i];
		}

		push_lazy(_r);
		for(int i=(_r*K); i<=r; i++){
			ret += arr[i];
		}
		return ret;
	}
}sq;