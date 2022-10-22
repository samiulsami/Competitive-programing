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

int odd[N]={0};
int even[N]={0};
int tmp[N];


void manacher(const string &s){
	int n = s.length();
	///even[i] stores the value for the right center of even length palindromes
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?1:min(odd[l+r-i+1],r-i+1);
		while(i-k>=0 && i+k<n && s[i-k]==s[i+k])k++;
		odd[i+1]=k;
		if(i+k-1>r){
			l=i-k+1;
			r=i+k-1;
		}
	}
	
	for(int i=0,l=0,r=-1,k; i<n; i++){
		k=(i>r)?0:min(even[l+r-i+2],r-i+1);
		while(i-k-1>=0 && i+k<n && s[i-k-1]==s[i+k])k++;
		even[i+1]=k;
		if(i+k-1>r){
			l=i-k;
			r=i+k-1;
		}
	}
}

struct wavelet_tree{///1 indexed
    int low,high;
    wavelet_tree *lft=NULL,*rgt=NULL;
    int *pref=NULL;
	long long *sum=NULL;
    wavelet_tree(int *l, int *r, int low, int high):low(low),high(high){
        if(l>=r || low>=high)return;
        pref = new int[r-l+2];
		sum = new long long[r-l+2];
        pref[0]=0;
		sum[0]=0;
        int mid = (low+high)>>1, cnt=1;
        for(int *i=l; i!=r; i++,cnt++){
			pref[cnt] = pref[cnt-1]+((*i)<=mid);
			sum[cnt] = sum[cnt-1] + (*i);
		}
        int *pivot = stable_partition(l,r,[&](int x){return x<=mid;});
        lft = new wavelet_tree(l, pivot, low, mid);
        rgt = new wavelet_tree(pivot, r, mid+1, high);
    }
    void swapAdjacent(int ind){///Swaps the elements at index 'ind' and 'ind+1'
        if(low==high)return;
        int firstBit=pref[ind]-pref[ind-1];
        if(firstBit==(pref[ind+1]-pref[ind])){
            if(firstBit)lft->swapAdjacent(pref[ind]);
            else rgt->swapAdjacent(ind-pref[ind]);
        }
        else{
            if(firstBit)pref[ind]--;
            else pref[ind]++;
        }
    }
    int Count(int l, int r, int k){///Count occurences of 'k' in range [l,r]
        if(l>r || high<k || low>k)return 0;
        if(low==high)return r-l+1;
        int mid = (low+high)>>1;
        if(k<=mid)return lft->Count(pref[l-1]+1, pref[r], k);
        return rgt->Count(l-pref[l-1], r-pref[r], k);
    }
    int kth(int l, int r, int k){///Returns the k'th smallest element in range [l,r]
        if(l>r)return 0;
        if(low==high)return low;
        int lftCount = pref[r]-pref[l-1];
        if(lftCount>=k)return lft->kth(pref[l-1]+1, pref[r], k);
        return rgt->kth(l-pref[l-1], r-pref[r], k-lftCount);
    }
    int LT(int l, int r, int k){///Returns the count of elements that are less than to 'k' in range [l,r]
        if(l>r || low>=k)return 0;
        if(high<k)return r-l+1;
        return lft->LT(pref[l-1]+1, pref[r], k) + rgt->LT(l-pref[l-1], r-pref[r], k);
    }
	long long sumQuery(int l, int r, int k){//Returns the sum of elements less than 'k' in range [l,r]
		if(l>r || low>=k)return 0;
		if(low==high)return 1LL*(r-l+1)*low;
        if(high<k){
			if(sum==NULL)return 0;
			return sum[r]-sum[l-1];
		}
        return lft->sumQuery(pref[l-1]+1, pref[r], k) + rgt->sumQuery(l-pref[l-1], r-pref[r], k);
	}
    ~wavelet_tree(){
        if(pref!=NULL)delete []pref;
		if(sum!=NULL)delete []sum;
        if(lft!=NULL)delete lft;
        if(rgt!=NULL)delete rgt;
    }
};

inline ll get(ll x){
	if(x==0)return 0;
	return (x*(x+1))/2LL;
}

inline ll iSum(int l, int r){
	return get(r)-get(l-1);
}

void solve(int casenum){
	string s;
	cin>>s;
	manacher(s);
	int n = sz(s);
	
	wavelet_tree *oddL,*evenL; ///C[i] - i
	wavelet_tree *oddR,*evenR; ///C[i] + i;
	
	for(int i=1; i<=n; i++)tmp[i] = odd[i] - i;
	oddL = new wavelet_tree(tmp+1, tmp+n+1, -n, 0);
	
	for(int i=1; i<=n; i++)tmp[i] = even[i] - i;
	evenL = new wavelet_tree(tmp+1, tmp+n+1, -n, 0);
	
	for(int i=1; i<=n; i++)tmp[i] = odd[i] + i;
	oddR = new wavelet_tree(tmp+1, tmp+n+1, 0, n);
	
	for(int i=1; i<=n; i++)tmp[i] = even[i] + i;
	evenR = new wavelet_tree(tmp+1, tmp+n+1, 0, n);
	
	ll ans,l,r,q,m;
	cin>>q;
	ll x;
	
	while(q--){
		cin>>l>>r;
		if(l==r){
			cout<<"1\n";
			continue;
		}
		ans=0;
		
		///odd left
		m = (l+r)>>1;
		ans += iSum(l,m);
		x = (m-l+1)-oddL->LT(l,m,1-l);
		ans += (1LL*x*(1-l));
		ans += oddL->sumQuery(l,m,1-l);
		
		///odd right
		ans -= iSum(m+1,r);
		x = (r-m)-oddR->LT(m+1, r, r+1);
		ans += (1LL*x*(r+1));
		ans += oddR->sumQuery(m+1,r, r+1);
		
		///even left
		ans += iSum(l,m);
		x = (m-l+1)-evenL->LT(l,m,-l);
		ans += (1LL*x*(-l));
		ans += evenL->sumQuery(l,m,-l);
		
		///odd right
		ans -= iSum(m+1,r);
		x = (r-m)-evenR->LT(m+1, r, r+1);
		ans += (1LL*x*(r+1));
		ans += evenR->sumQuery(m+1,r, r+1);
		
		cout<<ans<<"\n";
	}
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