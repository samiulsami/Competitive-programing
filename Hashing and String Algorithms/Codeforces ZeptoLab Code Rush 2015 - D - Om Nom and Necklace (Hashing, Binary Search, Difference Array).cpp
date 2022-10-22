#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
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
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e6+5;


  
const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};

vector<int>P[_hashCnt];

inline int mod(ll x) {
	if(x<mod1)return x;
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{
    vector<int>H[_hashCnt];
    int n;
    inline void initP(int ind){
        while((int)P[ind].size()<=n){
            if(P[ind].empty())P[ind].push_back(1);
            else P[ind].push_back(mod(1LL*P[ind].back()*bases[ind]));
        }
    }
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            initP(ind);
            H[ind].resize(n+1);H[ind][0]=0;
            for(int i=0;i<n; i++)
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll getHash(int l, int r){return _hashCnt==1?singleHash(l,r):combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};


int diff[N]={0};
char s[N];

void solve(int casenum){
	int n,k;
	sf("%d%d %s",&n,&k,&s);
	Hash H(s,n);
	
	for(int i=1; i<=n; i++){
		if(1LL*i*k>n)break;
		bool pos=1;
		ll prefhash = H.getHash(1,i);
		for(int j=1,x=i*k; j+i-1<=x; j+=i){
			if(H.getHash(j,j+i-1)!=prefhash){
				pos=0;
				break;
			}
		}
		if(pos){
			int last = k*i;
			diff[last]++;
			diff[last+1]--;
			
			int low=1,high=n-last+1,mid,cur=-1;
			while(low<=high){
				mid=(low+high)>>1;
				if(H.getHash(last+1,last+mid)==H.getHash(1,mid)){
					low=mid+1;
					cur=max(cur,mid);
				}
				else high=mid-1;
			}
			
			if(cur!=-1){
				cur=min(i,cur);
				diff[last+1]++;
				diff[last+1+cur]--;
			}
		}
		
	}

	int cnt=0;
	for(int i=1; i<=n; i++){
		cnt+=diff[i];
		if(cnt>0)s[i-1]='1';
		else s[i-1]='0';
	}
	s[n]='\0';
	pf("%s\n",s);
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}