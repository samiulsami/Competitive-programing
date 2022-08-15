#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

struct segtree{
	#define T array<int,2>
	T Tree[4*N];

	inline T Combine(T a, T b){
		return {min(a[0],b[0]),min(a[1],b[1])};
	}

	void build(int node, int l, int r){
		if(l==r){
			Tree[node] = {int(1e9),int(1e9)};
		}
		else{
			int mid = (l+r)>>1;
			build(node<<1,l,mid);
			build(node<<1|1,mid+1,r);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
	
	#undef T
}segtree;

int arr[N];
deque<int>lst[N];

inline void solve(int caseNum){
	int n,k;
	cin>>n>>k;

	for(int i=1; i<=n; i++){
		cin>>arr[i];
		lst[arr[i]].push_back(i);
	}
	segtree.build(1,1,k);

	for(int i=1; i<=k; i++){
		segtree.update(1,1,k,i,{lst[i].front(),lst[i].back()});
	}

	///min element whose min position is less than max position of all others
	for(int x=1; x<=k; x++){
		int low=1,high=k,mid,ans=-1;
		while(low<=high){
			mid = (low+high)>>1;
			auto xd = segtree.query(1,1,k,1,mid);
			int mx = segtree.Tree[1][1];
			if(xd[0]<=mx){
				high=mid-1;
				ans=mid;
			}
			else low=mid+1;
		}
		
		int ind = lst[ans].front();
		//lst[ans].clear();
		segtree.update(1,1,k,ans,{int(1e9),int(1e9)});
		cout<<ans<<" ";
		while(segtree.Tree[1][0]<=ind){
			//cerr<<segtree.Tree[1][0]<<" "<<ind<<"\n";
			int curind = segtree.Tree[1][0];
			int curval = arr[curind];
			while(!lst[curval].empty() && lst[curval].front()<=ind)
				lst[curval].pop_front();
			
			int l,r;
			if(lst[curval].empty()){
				l=1e9;
				r=1e9;
			}
			else{
				l = lst[curval].front();
				r = lst[curval].back();
			}
			segtree.update(1,1,k,curval,{l, r});
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