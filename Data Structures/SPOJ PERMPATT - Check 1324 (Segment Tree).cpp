#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;

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

int arr[N];
int suffmax[N];

inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>arr[i];
		suffmax[i]=-1;
	}
	segtree<int> st(n+5,N+N, [](int a, int b)->int{return min(a,b);});
	suffmax[n]=-1;
	suffmax[n-1]=arr[n-1];
	for(int i=n-2; i>=0; i--)suffmax[i] = max(suffmax[i+1], arr[i]);

	int prefmin=arr[0];
	for(int i=1; i<n; i++){
		if(arr[i]<prefmin){
			prefmin=arr[i];
			continue;
		}

		if(suffmax[i+1]>arr[i] && (arr[i]+1)!=suffmax[i+1]){
			if(st.query(arr[i]+1, suffmax[i+1]-1) < arr[i]){
				cout<<"yes\n";
				return;
			}
		}

		st.update(arr[i], prefmin);
	}
	cout<<"no\n";
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