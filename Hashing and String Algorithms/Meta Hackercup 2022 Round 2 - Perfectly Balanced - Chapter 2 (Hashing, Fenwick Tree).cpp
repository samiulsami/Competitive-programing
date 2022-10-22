#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// ///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
// ///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
// template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N = 1e6+5;
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int64_t rand(int64_t l, int64_t r){uniform_int_distribution<int64_t> RNG(l,r);return RNG(rng);}

typedef uint64_t ull;

ull BIT[N];
int arr[N];
int n;

void update(int ind, ull val){
    while(ind<=n){
        BIT[ind]+=val;
        ind+=(ind&-ind);
    }
}

ull query(int ind){
    ull ret=0;
    while(ind>0){
        ret+=BIT[ind];
        ind-=(ind&-ind);
    }
    return ret;
}

inline ull query(int l, int r){
	return query(r)-query(l-1);
}

ull BIT2[N];

void update2(int ind, ull val){
    while(ind<=n){
        BIT2[ind]^=val;
        ind+=(ind&-ind);
    }
}

ull query2(int ind){
    ull ret=0;
    while(ind>0){
        ret^=BIT2[ind];
        ind-=(ind&-ind);
    }
    return ret;
}

inline ull query2(int l, int r){
	return query2(r)^query2(l-1);
}

inline void solve(int caseNum){
	cin>>n;
	map<int,ull>mp;
	set<uint64_t>st;

	for(int i=0; i<=n+1; i++){
		BIT[i]=0;
		BIT2[i]=0;
	}

	for(int i=1; i<=n; i++){
		cin>>arr[i];

		if(!mp.count(arr[i])){
			ull tmp = rng();
			while(st.count(tmp))tmp = rng();
			mp[arr[i]]=tmp;
			st.insert(tmp);
		}
		update(i,mp[arr[i]]);
		update2(i,mp[arr[i]]);
	}

	int q,qt;
	cin>>q;

	int l,r;
	int ans=0;
	for(int xd=0; xd<q; xd++){

		cin>>qt>>l>>r;
		if(qt==2){
			if((r-l+1)%2==0)continue;

			ull tmp = query2(l,r);
			if(!st.count(tmp))continue;
			ull _xl=0,_xr=0;
			int len = (r-l+2)/2;
			_xl = query(l,l+len-1);
			_xr = query(l+len, r);

			if((_xr-tmp)==_xl || (_xl-tmp)==_xr){
				//dbug(xd);
				ans++;
				continue;
			}

			_xl=0,_xr=0;
			len = (r-l+1)/2;
			_xl = query(l,l+len-1);
			_xr = query(l+len, r);
			
			if((_xr-tmp)==_xl || (_xl-tmp)==_xr){
				//dbug(xd);
				ans++;
				continue;
			}
		}
		else{
			update(l,-mp[arr[l]]);
			update2(l,mp[arr[l]]);
			if(!mp.count(r)){
				ull tmp = rng();
				while(st.count(tmp))tmp = rng();
				mp[r]=tmp;
				st.insert(tmp);
			}
			arr[l] = r;
			update(l,mp[arr[l]]);
			update2(l,mp[arr[l]]);
		}
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