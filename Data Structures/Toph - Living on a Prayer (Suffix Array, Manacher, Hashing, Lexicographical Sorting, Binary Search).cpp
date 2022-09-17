#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e4+5;

///0 indexed
///Don't insert '#' at the beginning of the string
///LCP[i] is the LCP of SA[i] and SA[i-1]
///invSA[i] is the position of 'i' in the suffix array
///LCP of the substrings beginning at indices 'l' and 'r' = LCP(invSA[l]+1, invSA[r]) (swap l and r if invSA[l]<invSA[r])
///O(nlogn) Time and Memory

const int K=__lg(N)+2;
struct SuffixArray{///0 indexed
    int SA[N],LCP[N],invSA[N];
    int RA[N],c[N+200],n;
    int Table[K][N]={{0}};
    inline void countingSort(int k){
        int mx = max(130,n),i,j,sum;
		fill(c,c+mx+5,0);
		for(i=0; i<n; i++)c[i+k<n ? RA[i+k]:0]++;
		for(i=0,sum=0; i<mx; i++){j=c[i],c[i]=sum,sum+=j;}
		for(i=0; i<n; i++)invSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];
		for(i=0; i<n; i++)SA[i]=invSA[i];
    }
    void init(const string &s){
		int i,k,j;
		n = (int)s.size();
		auto cmp = [&](int &a, int &b)->bool{
			if(RA[a]^RA[b])return RA[a]<RA[b];
			return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
		};
		for(i=0; i<n; i++)SA[i]=i,RA[i]=s[i];
		for(k=1; k<n; k<<=1){
			countingSort(k);
			countingSort(0);
			invSA[0]=1;
			for(i=1; i<n; i++)invSA[i]=invSA[i-1]+cmp(SA[i-1],SA[i]);
			for(i=0; i<n; i++)RA[SA[i]]=invSA[i];
			if(invSA[n-1]==n)break;
		}
		for(i=0; i<n; i++)invSA[SA[i]]=i;
		for(i=0,k=0; i<n; i++){
			if(invSA[i]==0)k=0;
			else{
				j=SA[invSA[i]-1];
				while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;
				LCP[invSA[i]]=k;
				Table[0][invSA[i]]=k;
				if(k>0)k--;
				else k=0;
			}
		}
		//for(i=0; i<n; i++)cout<<setw(2)<<SA[i]<<", LCP: "<<LCP[i]<<" "<<s.substr(SA[i])<<endl;
		for(i=1; i<=K; i++)for(j=0; j+(1<<i)-1<n; j++)Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
    }
    inline int lcp(int l, int r){
    	assert(l<=r);
        int lg=__lg(r-l+1);
        return min(Table[lg][l],Table[lg][r-(1<<lg)+1]);
    }

    inline int lcp2(int l, int r){
    	l = invSA[l];
    	r = invSA[r];
    	if(l>r)swap(l,r);
    	l++;
    	return lcp(l,r);
    }

    int countOcc(int l, int len){
    	l = invSA[l];
    	int low=l+1,high=n-1,mid,upper=l,lower=l;
    	while(low<=high){
    		mid = (low+high)>>1;
    		if(lcp(l+1,mid)<len)high=mid-1;
    		else{
    			upper = mid;
    			low=mid+1;
    		}
    	}

    	low=0,high=l-1;
    	while(low<=high){
    		mid = (low+high)>>1;
    		if(lcp(mid+1,l)<len)low=mid+1;
    		else{
    			high=mid-1;
    			lower=mid;
    		}
    	}

    	return upper-lower+1;
    }
}SA;

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

mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const uint64_t mod1 = (1uLL<<61) - 1;
inline uint64_t hashmodmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod1) + (ret>>61);
    ret = (ret & mod1) + (ret>>61);
    return ret-1;
}
inline uint64_t hashAdd(uint64_t a, uint64_t b){a+=b;return a>=mod1?a-mod1:a;}
inline uint64_t hashSub(uint64_t a, uint64_t b){a-=b;return a>=mod1?a+mod1:a;}
const uint64_t base1 = (uint64_t)1541 + (uint64_t)rng()%(uint64_t)(1<<22);
uint64_t P[N];

struct Hash{///0 indexed
    vector<uint64_t>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
        n = int(s.size());
        H.resize(n+1);H[0]=0;
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
        }
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r+1], hashmodmul(H[l], P[r-l+1]));}
};

inline void solve(int caseNum){
	string s;
	int k;
	cin>>s>>k;
	manacher(s);
	Hash H(s);
	set<uint64_t>st[sz(s)];
	vector<pii(2)>palindromes;

	for(int i=0; i<sz(s); i++){
		int l = i-odd[i]+1;
		int r = i+odd[i]-1;
		while(l<=r && !st[r-l].count(H.fHash(l,r))){
			palindromes.push_back({l,r});
			st[r-l].insert(H.fHash(l,r));
			l++,r--;
		}

		if(even[i]==0)continue;
		l = i-even[i];
		r = i+even[i]-1;

		while(l<=r && !st[r-l].count(H.fHash(l,r))){
			palindromes.push_back({l,r});
			st[r-l].insert(H.fHash(l,r));
			l++,r--;
		}
	}

	SA.init(s);
	sort(all(palindromes), [&](auto &L, auto &R)->bool{
		int lenL = L[1]-L[0]+1;
		int lenR = R[1]-R[0]+1; 
		if(L[0]==R[0])return lenL<lenR;
		int lcp = min({lenL, lenR,SA.lcp2(L[0], R[0])});
		if(lcp == lenL || lcp == lenR)return lenL<lenR;
		return s[L[0]+lcp] < s[R[0]+lcp];
	});
	//cout<<caseNum<<"--------\n";
	//for(auto xd:palindromes)cout<<s.substr(xd[0], xd[1]-xd[0]+1)<<endl;

	for(auto &p:palindromes){
		k -= SA.countOcc(p[0], p[1]-p[0]+1);
		if(k<=0){
			cout<<s.substr(p[0],p[1]-p[0]+1)<<"\n";
			return;
		}
	}

	cout<<"-1\n";
}

int main(){
	P[0]=1;
	for(int i=1; i<N; i++)P[i] = hashmodmul(P[i-1],base1);
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}