struct rmq{///0 indexed
	#define T int
	static const int K=__lg(N)+2;
	T Table[K][N];
	
	inline T Combine(T &a, T &b){
		return min(a,b);
	}
	
	void init(int *arr, int len){
		for(int i=0; i<len; i++)Table[0][i] = arr[i];
		for(int i=1; i<=K; i++)
			for(int j=0; j+(1<<i)-1<len; j++)
				Table[i][j] = Combine(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
	}
	
	T query(int l, int r){
		int lg=__lg(r-l+1);
		return Combine(Table[lg][l], Table[lg][r-(1<<lg)+1]);
	}
	
	T query1(int l, int r){
		T ret;
		bool first=1;
		for(int k=K; k>=0; k--){
			if(l+(1<<k)-1<=r){
				if(first){
					ret = Table[k][l];
					first=0;
				}
				else ret = Combine(ret, Table[k][l]);
				l += (1<<k);
			}
		}		
		return ret;
	}
	
	#undef T
}rmq;