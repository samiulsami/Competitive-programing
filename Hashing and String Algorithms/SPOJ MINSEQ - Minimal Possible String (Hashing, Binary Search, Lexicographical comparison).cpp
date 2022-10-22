#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;
const int MOD = (1LL<<31)-1;
const int base = 1521+rng()%(1<<22);
int P[N];
int lim = N-2;

inline int mul(ll x, int b) {
	x*=b;
    if(x<MOD)return x;
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

inline int add(ll a, int b){a+=b; return a>=MOD?a-MOD:a;}
inline int sub(ll a, int b){a-=b; return a<0?a+MOD:a;}

int Ha[N],Hb[N];

inline void solve(int caseNum){
	string a,b;
	while(cin>>a){
		cin>>b;

		int n = a.length(), m = b.length();
		for(int i=0; i<n; i++){
			Ha[i] = mul(P[i], a[i]);
			if(i)Ha[i] = add(Ha[i], Ha[i-1]);
		}

		for(int i=0; i<m; i++){
			Hb[i] = mul(P[i], b[i]);
			if(i)Hb[i] = add(Hb[i], Hb[i-1]);
		}
		///0 1 2 '3' '4' '5' '6' 7 8
		///a = 5, b = 4, inserted at 3

		auto getHash = [&](int ins, int r)->int{///returns hash of string a[0...r] after inserting string 'b' at position 'ins'

			if(r<ins)return mul(Ha[r], P[lim-r]);///r lies before string 'b' after insertion at position 'ins'

			if(r<ins+m){///r lies inside string 'b' after insertion at position 'ins'
				int _ap = 0;
				if(ins>0)_ap = Ha[ins-1];
				int _ab = add(_ap,mul(Hb[r-ins], P[ins]));
				return mul(_ab, P[lim-r]);
			}

			int _ap = 0;
			if(ins>0)_ap = Ha[ins-1];
			int _ab = add(_ap, mul(Hb[m-1], P[ins]));

			int cur = sub(Ha[r-m], _ap);
			cur = mul(cur, P[m]);
			cur = add(cur, _ab);
			return mul(cur, P[lim-r]);
		};

		auto get = [&](int ins, int i)->char{
			if(i<ins)return a[i];
			if(i<ins+m)return b[i-ins];
			return a[i-m];
		};

		vector<int>xd(n+1);
		for(int i=0; i<=n; i++)xd[i]=i;

		int hehe = *min_element(all(xd),[&](int l, int r)->bool{
			int low=0,high=n+m-1,ans=-1,mid;
			while(low<=high){
				mid = (low+high)>>1;
				if(getHash(l,mid) == getHash(r,mid)){
					low=mid+1;
					ans=mid;
				}
				else high=mid-1;
			}

			if(ans==(n+m-1))return 0;
			if(ans==-1){
				if(l==0)return b[0]<a[0];
				return a[0]<b[0];
			}
		
			return get(l,ans+1)<get(r,ans+1);
		});

		int i=0;
		string ans;
		while(i<hehe)ans.push_back(a[i++]);
		ans += b;
		while(i<n)ans.push_back(a[i++]);

		cout<<ans<<"\n";
	}

}

int main(){
	P[0]=1;
	for(int i=1; i<N; i++)P[i] = mul(P[i-1],base);
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}