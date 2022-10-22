#include<bits/stdc++.h>
using namespace std;

typedef uint64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
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
vector<uint64_t>P{1};

struct Hash{///1 indexed
    vector<uint64_t>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
    	n = int(s.size());
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        H.resize(n+1);H[0]=0;
        for(int i=0; i<n; i++)
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
};

inline void solve(int caseNum){
	int n,k;
	cin>>n>>k;
	vector<int>A(n+n,0),B(n);

	for(int i=0; i<n; i++){
		cin>>A[i];
		A[i+n]=A[i];
	}	
	for(int i=0; i<n; i++)cin>>B[i];

	Hash HA(A);
	Hash HB(B);

	bool possible;
	if(n==2){
		bool zeroPossible=0;
		bool onePossible=0;
		if(HA.fHash(1,n)==HB.fHash(1,n))zeroPossible=1;
		if(HA.fHash(2,n+1)==HB.fHash(1,n))onePossible=1;

		k%=2;
		if((k==1 && onePossible) || (k==0 && zeroPossible))possible=1;
		else possible=0;
	}
	else{
		bool zeroPossible = bool(HA.fHash(1,n)==HB.fHash(1,n));
		bool nonZeroPossible = 0;
		for(int i=n+1; !nonZeroPossible && i<n+n; i++)
			nonZeroPossible |= bool(HA.fHash(i-n+1,i) == HB.fHash(1,n));

		if(k==0)possible = zeroPossible;
		else if(k==1)possible = nonZeroPossible;
		else possible = zeroPossible|nonZeroPossible;
	}
	cout<<"Case #"<<caseNum<<": ";
	if(possible)cout<<"YES\n";
	else cout<<"NO\n";
}

int main(){
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