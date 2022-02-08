#include<bits/stdc++.h>
using namespace std;

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


const int N = 1e5+5;


const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
	ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod1) + (ret>>61);
	ret = (ret & mod1) + (ret>>61);
	return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = (ull)1541 + (ull)rng()%(ull)(1<<22);
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    vector<ull>R;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1),R(n+2){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0,j=n+1; j>=2 && i<n; i++,j--){
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
            R[j-1] = hashAdd(hashmodmul(R[j], base1), (ull)s[j-2]);
        }
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
    ull reverseHash(int l, int r){return hashSub(R[l], hashmodmul(R[r+1], P[r-l+1]));}
};


void solve(int casenum){
	string s,ans1,ans2;
	cin>>s;
	bool arr[26];
	for(int i=0; i<26; i++)arr[i]=0;
	
	int ax=-1,ay=-1,bx=-1,by=-1;
	int lastInd=-1;
	char ch;
	for(int i=s.length()-1; i>=0; i--){
		if(i==s.length()-1)ch=s[i];
		else ch = min(ch,s[i]);
		if(s[i]>ch)lastInd=i;
	}
	ax=lastInd;
	if(lastInd==-1){
		ans1=s;
	}
	else{
		
		vector<int>indices;
		Hash H(s, sz(s));
		
		for(int j=lastInd+1; j<sz(s); j++){
			if(s[j]<s[lastInd])indices.push_back(j);
		}
		
		int id = *min_element(all(indices), [&](int i, int j)->bool{
			
			int len = min(i-lastInd+1, j-lastInd+1);
			int low=1,mid,high=len;
			int firstMismatch=1e9;
			
			while(low<=high){
				mid = (low+high)>>1;
				if(H.getHash(i-mid+2, i+1) == H.getHash(j-mid+2,j+1)){
					low=mid+1;
				}
				else{
					firstMismatch=min(firstMismatch,mid);
					high=mid-1;
				}
			}
			
			if(firstMismatch==1e9){
				int ii=min(i,j), jj = max(i,j);
				int len2 = min(sz(s)-ii-1, jj-len-lastInd+1);
				low=1,high=len2;
				firstMismatch=1e9;
				while(low<=high){
					mid = (low+high)>>1;
					if(H.getHash(ii+2,ii+2+mid-1) == H.reverseHash(jj-len+1 - mid+1, jj-len+1)){
						low=mid+1;
					}
					else {
						firstMismatch=mid;
						high=mid-1;
					}
				}
				bool xx = (i!=min(i,j));
				//if(ii==2 && jj==9)dbug(firstMismatch);
				if(firstMismatch==1e9){
					return bool(i>j);
				}
				return xx^bool(s[ii+firstMismatch]<s[jj-len-firstMismatch+1]);
			}
			//cout<<i<<" "<<j<<" "<<firstMismatch<<"-> "<<s[i]<<" "<<s[j]<<", "<<s[i-firstMismatch+1]<<" "<<s[j-firstMismatch+1]<<endl;
			return s[i-firstMismatch+1]<s[j-firstMismatch+1];
		});
		ans1=s;
		ay=id;
		for(int i=lastInd,j=id; i<=j; i++,j--)swap(ans1[i],ans1[j]);
	}
	
	cout<<ans1<<endl;
	// ans2=s;
	// string tmp;

	// for(int i=0; i<sz(s); i++){
		// for(int j=i+1; j<sz(s); j++){
			// tmp=s;
			// for(int x=i,y=j; x<y; x++,y--)swap(tmp[x],tmp[y]);
			// if(tmp<ans2){
				// bx=i;
				// by=j;
				// ans2=tmp;
			// }
		// }
	// }
	
	// if(ans1!=ans2){
		// cout<<"given string: "<<s<<endl;
		// cout<<ans1<<" "<<ans2<<endl;
		// cout<<ax<<" "<<ay<<endl;
		// cout<<bx<<" "<<by<<endl;
		// cout<<"--------------------------------------------\n"<<endl;
	// }
}
/*fail case
given string: baababbbaa
aabbbabaab aabbabbbaa
0 9
0 2
*/
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

//    freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}