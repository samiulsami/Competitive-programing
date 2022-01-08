vector<int> Z_Algo(const string &s){
	int n = (int)s.size();
	vector<int>Z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	return Z;
}