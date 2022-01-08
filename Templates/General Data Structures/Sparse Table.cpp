struct rmq{
	#define T ll
	static const int K=__lg(N)+2;
	bool precalc=0;
	T Table[K][N];
	int lgval[N];
	void init(T *arr, int len){
		if(!precalc){
			precalc=1;lgval[0]=lgval[1]=0;
			for(int i=2; i<N; i++)lgval[i]=lgval[i>>1]+1;
		}
		for(int i=0; i<len; i++)Table[0][i]=arr[i];
		for(int i=1; i<=K; i++)
			for(int j=0; j+(1<<i)-1<len; j++)
				Table[i][j] = __gcd(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
	}
	T query(int l, int r){
		int lg=lgval[r-l+1];
		return __gcd(Table[lg][l],Table[lg][r-(1<<lg)+1]);
	}
	#undef T
}rmq;