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

template<typename T>
struct segtree{/// 0 indexed
	T *Tree=NULL;
	int n;
	function<T(T,T)> Combine;

	segtree(){}
	~segtree(){delete []Tree;}
	segtree(int x, T id, function<T(T,T)> _cmb):n(x){
		Combine = _cmb;
		Tree = new T[4*n];
		fill(Tree,Tree+4*n,id);
	}

	template<typename Iterator>
	segtree(Iterator l, Iterator r, function<T(T,T)> _cmb):segtree(vector<T>(l,r), _cmb){}
	segtree(const vector<T> &arr, function<T(T,T)> _cmb){
		Combine = _cmb;
		n = int(arr.size());
		Tree = new T[4*n];
		build(1,0,n-1,arr);
	}

	void build(int node, int l, int r, const vector<T> &arr){
		if(l==r)Tree[node] = arr[l];
		else{
			int mid = (l+r)>>1;
			build(node<<1, l, mid, arr);
			build(node<<1|1, mid+1, r, arr);
			Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
		}
	}

	void update(int pos, T val){update(1,0,n-1,pos,val);}
	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=Combine(Tree[node], val);
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	T query(int l, int r){return query(1,0,n-1,l,r);}
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
};

inline void solve(int caseNum){
	int n,q;
	cin>>n>>q;
	map<pair<int, uint64_t>, int>mp;

	for(int i=0; i<n; i++){
		string s;
		cin>>s;
		
		set<uint64_t>st[sz(s)];
		Hash H(s);

		for(int j=0; j<sz(s); j++){
			int low=1,high=min(j+1,sz(s)-j),mid,odd=1;

			while(low<=high){
				mid = (low+high)>>1;
				if(H.fHash(j-mid+1, j+mid-1) == H.rHash(j-mid+1, j+mid-1)){
					low=mid+1;
					odd=mid;
				}
				else high=mid-1;
			}

			int l = j-odd+1;
			int r = j+odd-1;
			while(l<=r && !st[r-l].count(H.fHash(l,r))){
				st[r-l].insert(H.fHash(l,r));
				l++;
				r--;
			}

			if(j==sz(s)-1 || s[j]!=s[j+1])continue;

			low=1,high=min(j+1,sz(s)-j-1);
			int even=1;

			while(low<=high){
				mid = (low+high)>>1;
				if(H.fHash(j-mid+1, j+mid) == H.rHash(j-mid+1, j+mid)){
					low=mid+1;
					even=mid;
				}
				else high=mid-1;
			}	

			l=j-even+1;
			r=j+even;
			while(l<=r && !st[r-l].count(H.fHash(l,r))){
				st[r-l].insert(H.fHash(l,r));
				l++;
				r--;
			}
		}

		for(int len=0; len<sz(s); len++)
			for(auto xd:st[len])
				mp[{len+1,xd}]++;
		
	}

	segtree<int> st(n, 0, [&](int a, int b)->int{return max(a,b);});

	for(auto it:mp)
		st.update(it.second-1, it.first.first);

	for(int i=0,l,r; i<q; i++){
		cin>>l>>r;
		cout<<st.query(l-1,r-1)<<"\n";
	}
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