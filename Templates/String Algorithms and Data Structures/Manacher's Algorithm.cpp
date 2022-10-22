int odd[N];
int even[N];

void manacher(const string &s){///0 indexed
	int n = s.length();
	fill(odd,odd+n,0);
	fill(even,even+n,0);
	///odd[i] =  radius of the longest odd palindrome centered at i (indices i-odd[i]+1 to i+odd[i]-1 inclusive)
	///even[i] = radius of the longest even palindrome centered at index i and i-1 (indices i-even[i] to i+even[i]-1 inclusive)
	///even[i] is 0 if no even palindrome is centered at index i
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?1:min(odd[l+r-i],r-i+1);
		while(i-k>=0 && i+k<n && s[i-k]==s[i+k])k++;
		odd[i]=k;
		if(i+k-1>r){
			l=i-k+1;
			r=i+k-1;
		}
	}
	
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?0:min(even[l+r-i+1],r-i+1);
		while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k])k++;
		even[i]=k;
		if(i+k-1>r){
			l=i-k;
			r=i+k-1;
		}
	}
}

inline bool isPal(int l, int r){
	int len = (r-l+1);
	if(len&1)return l+2*odd[l+(len>>1)]-2>=r;
	return l+2*even[l+(len>>1)]-1>=r;
}