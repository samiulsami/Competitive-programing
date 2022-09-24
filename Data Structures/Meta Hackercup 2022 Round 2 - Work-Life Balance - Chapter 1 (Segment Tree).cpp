#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<ll,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e6+5;

struct segtree{
	pii(3) Tree[4*N];

	inline pii(3) Combine(pii(3) a, pii(3) b){return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};}

	void update(int node, int l, int r, int pos, pii(3) val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}
	
	pii(3) query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
}st;

inline void solve(int caseNum){
	int n,m;
	cin>>n>>m;
	for(int i=0; i<=4*n; i++){
		st.Tree[i] = {0,0,0};
	}

	for(int i=1,x; i<=n; i++){
		cin>>x;
		pii(3) tmp{0,0,0};
		tmp[x-1]=1;
		st.update(1,1,n,i,tmp);
	}

	ll ans=0;

	for(ll i=0,x,y,z,sumL,sumR; i<m; i++){
		cin>>x>>y>>z;

		{
			pii(3) tmp{0,0,0};
			tmp[y-1]=1;
			st.update(1,1,n,x,tmp);
		}

		auto L = st.query(1,1,n,1,z);
		auto R = st.query(1,1,n,z+1,n);
		sumL=L[0]+(2*L[1])+(3*L[2]);
		sumR=R[0]+(2*R[1])+(3*R[2]);
		if(sumL==sumR)continue;

		if(sumL<sumR){
			swap(L,R);
			swap(sumL,sumR);
		}

		ll add=0;
		ll dist = sumL-sumR;
		///left is greater

		for(ll u=2; dist>0 && u>=0; u--){
			for(ll v=0; dist>0 && v<u; v++){
				if(L[u]==0 || R[v]==0)continue;
				ll low = 1, high = min(L[u],R[v]),mid,cur=-1;
				ll weight = (u-v)*2LL;

				while(low<=high){
					mid = (low+high)>>1;
					if((mid*weight)<=dist){
						cur = mid;
						low=mid+1;
					}
					else high=mid-1;
				}

				if(cur!=-1){
					dist -= (weight*cur);
					L[u] -= cur;
					R[v] -= cur;
					add += cur;
				}
			}
		}

		if(dist!=0){
			ans--;
		}
		else ans += add;
		
	}

	cout<<"Case #"<<caseNum<<": "<<ans<<"\n";
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