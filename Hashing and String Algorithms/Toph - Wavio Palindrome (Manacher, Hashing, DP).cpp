#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

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
uint64_t P[1000002];

struct Hash{///0 indexed
    vector<uint64_t>H;
   // vector<uint64_t>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
        n = int(s.size());
        H.resize(n+1);H[0]=0;
       // R.resize(n+2);R[n+1]=0;R[0]=0;
        for(int i=0; i<n; i++){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
            //R[j-1] = hashAdd(hashmodmul(R[j], base1), (uint64_t)s[j-2]);
        }
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r+1], hashmodmul(H[l], P[r-l+1]));}
    //inline uint64_t rHash(int l, int r){return hashSub(R[l+1], hashmodmul(R[r+2], P[r-l+1]));}
};

Hash H;
map<uint64_t, int>mp[1000001];

int odd[1000001];
int even[1000001];

void manacher(const string &s){
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

bool isPal(int l, int r){
	int len = (r-l+1);
	if(len&1)return l+2*odd[l+(len>>1)]-2>=r;
	return l+2*even[l+(len>>1)]-1>=r;
}

int isWavio(int l, int r){
	if(l>r)return 0;
	if(!isPal(l,r))return 0;
	return isPal(l, l+(r-l+2)/2 - 1);
}

ll f(uint64_t h, int l, int r){
	if((r-l+1)<3)return 0;
	if(mp[r-l].count(h))return mp[r-l][h];
	return mp[r-l][h] = isWavio(l,r) + f(H.fHash(l+1,r-1), l+1, r-1);
}

inline void solve(int caseNum){
	int n;
	string s;
	cin>>n>>s;
	manacher(s);
	H = Hash(s);

	ll ans=0;
	for(int j=0; j<sz(s); j++){

		int l = j-odd[j]+1;
		int r = j+odd[j]-1;
		ans += f(H.fHash(l,r), l, r);
		if(even[j]==0)continue;

		l=j-even[j];
		r=j+even[j]-1;
		ans += f(H.fHash(l,r), l, r);
	}
	for(int i=0; i<sz(s); i++)mp[i].clear();
	cout<<"Case "<<caseNum<<": "<<ans<<"\n";
}

int main(){
	P[0]=1;
	for(int i=1; i<=1000001; i++)P[i] = hashmodmul(P[i-1],base1);
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