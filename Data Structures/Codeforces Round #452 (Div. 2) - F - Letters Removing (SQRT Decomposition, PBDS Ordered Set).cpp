#include<bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 2e5+5;
const int DIV = 450;

string s;
deque<int> Block[62][DIV];

inline int get(char c){
	if(c>='a' && c<='z')return (int)c-'a';
	if(c>='A' && c<='Z')return (int)c-'A'+26;
	return (int)c-'0'+52;
}

void solve(int casenum){
	int n,m,l,r,ll,rr,k;
	char c;
	cin>>n>>m>>s;
	orderSet<int>st;
	
	for(int i=0; i<n; i++){
		Block[get(s[i])][i/DIV].push_back(i);
		st.insert(i);
	}
	
	while(m--){
		cin>>l>>r>>c;
		c=get(c);
		l=*st.find_by_order(l-1);
		r=*st.find_by_order(r-1);
		ll=l/DIV;
		rr=r/DIV;
		
		if(ll==rr){
			if(!Block[c][ll].empty()){
				Block[c][ll].clear();
				for(int i=ll*DIV,x=(ll+1)*DIV; i<x; i++){
					if(s[i]!='#' && get(s[i])==c){
						if(i>=l && i<=r){
							s[i]='#';
							st.erase(i);
						}
						else Block[c][ll].push_back(i);
					}
				}
			}
		}
		else{
			while(!Block[c][ll].empty()){
				k=Block[c][ll].back();
				if(k<l)break;
				s[k]='#';
				st.erase(k);
				Block[c][ll].pop_back();
			}
			
			while(!Block[c][rr].empty()){
				k=Block[c][rr].front();
				if(k>r)break;
				s[k]='#';
				st.erase(k);
				Block[c][rr].pop_front();
			}
			
			for(int i=ll+1; i<rr; i++){
				while(!Block[c][i].empty()){
					k=Block[c][i].back();
					s[k]='#';
					st.erase(k);
					Block[c][i].pop_back();
				}
			}
			
		}
		
	}
	
	for(char c:s)if(c!='#')cout<<c;
	cout<<endl;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}