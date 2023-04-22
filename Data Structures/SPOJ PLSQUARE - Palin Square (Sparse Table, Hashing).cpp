#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 205;
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

struct Hash{///0 indexed
    vector<uint64_t>H;
    vector<uint64_t>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s){
        n = int(s.size());
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        H.resize(n+1);H[0]=0;
        R.resize(n+2);R[n+1]=0;R[0]=0;
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (uint64_t)s[i]);
            R[j-1] = hashAdd(hashmodmul(R[j], base1), (uint64_t)s[j-2]);
        }
    }
    inline uint64_t fHash(int l, int r){return hashSub(H[r+1], hashmodmul(H[l], P[r-l+1]));}
    inline uint64_t rHash(int l, int r){return hashSub(R[l+1], hashmodmul(R[r+2], P[r-l+1]));}
};

string grid[205];
Hash horizontal[205];
Hash vertical[205];

struct rmq{///0 indexed
	#define T int
	static const int K=__lg(N)+2;
	T Table[K][N];
	
	inline void set(int pos, T val){Table[0][pos]=val;}

	void init(int n){
		for(int i=1; i<=K; i++)
			for(int j=0; j+(1<<i)-1<n; j++)
				Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
	}
	
	T query(int l, int r){
		int lg=__lg(r-l+1);
		return min(Table[lg][l], Table[lg][r-(1<<lg)+1]);
	}
	
	#undef T
}rmq[4][201];///0 = oddrow, 1 = oddcolumn, 2 = evenrow, 3 = evencolumn

int n;
int get(Hash &h, int i, bool odd){
	if(odd){
		int low=1,high=min(i+1,n-i),mid,ret=1;
		while(low<=high){
			mid = (low+high)>>1;
			if(h.fHash(i-mid+1,i+mid-1)==h.rHash(i-mid+1,i+mid-1))low=mid+1,ret=mid;
			else high=mid-1;
		}
		return ret+ret-1;
	}

	int low=0,high=min(i+1,n-i-1),mid,ret=0;

	while(low<=high){
		mid = (low+high)>>1;
		if(h.fHash(i-mid+1,i+mid) == h.rHash(i-mid+1,i+mid))low=mid+1,ret=mid;
		else high=mid-1;
	}

	return ret*2;
}

inline void solve(int caseNum){
	cin>>n;

	for(int i=0; i<n; i++){
		cin>>grid[i];
		horizontal[i] = Hash(grid[i]);
	}

	for(int i=0; i<n; i++){
		string x;
		for(int j=0; j<n; j++)x.push_back(grid[j][i]);
		vertical[i] = Hash(x);
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			rmq[0][i].set(j,get(vertical[j],i,1));
			rmq[2][i].set(j,get(vertical[j],i,0));
			//dbug(get(vertical[j],i,1));
		}
	}


	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			rmq[1][j].set(i,get(horizontal[i],j,1));
			rmq[3][j].set(i,get(horizontal[i],j,0));
			//dbug(get(horizontal[i],j,1));
		}
	}

	for(int x=0; x<4; x++){
			for(int j=0; j<n; j++)rmq[x][j].init(n);
	}

	for(int x=n; x>=1; x--){
		int add=2;
		if(x&1)add=0;
		for(int i=0; i+x-1<n; i++){
			for(int j=0; j+x-1<n; j++){
				int mn = INT_MAX;
				int a = (i+i+x-1)/2;
				int b = (j+j+x-1)/2;
				// if(x%2==0){
				// 	a--;
				// 	b--;
				// }
				mn = min(mn, rmq[add][a].query(j,j+x-1));
				mn = min(mn, rmq[add+1][b].query(i,i+x-1));
				///dbug(mn);
				if(mn==x){
					cout<<x;
					return;
				}
			}
		}
	}
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}