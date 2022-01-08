const int N = 1001;

int BIT[N+1][N+1];

int query(int x, int y){
	int ret=0;
	for(int i=x; i>0; i -= i&-i)
		for(int j=y; j>0; j -= j&-j)
			ret+=BIT[i][j];
	return ret;
}

void update(int x, int y, int val){
	for(int i=x; i<=N; i += i&-i)
		for(int j=y; j<=N; j += j&-j)
			BIT[i][j]+=val;
}

int getAns(int x1, int y1, int x2, int y2){///Number of points in the rectangle (x1,y1), (x2,y2) (assuming (x2,y2)>(x1,x1))
	return query(x2,y2) + query(x1-1,y1-1) - query(x2,y1-1) - query(x1-1,y2);
}
