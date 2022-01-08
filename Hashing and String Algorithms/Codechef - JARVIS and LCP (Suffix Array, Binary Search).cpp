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
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e6+5;
const int K=__lg(N)+1;
struct SuffixArray{
    int SA[N],LCP[N],invSA[N],RA[N],n;
    int Table[K][N];
	int lgval[N];
    void init(const vector<int> &s){
        n=(int)s.size();
        int k,i,j;
        for(i=0; i<n; i++)RA[i]=s[i],SA[i]=i;
        auto cmp = [&](int &a, int &b)->bool{
            if(RA[a]^RA[b])return RA[a]<RA[b];
            return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
        };
        for(k=1; k<n ;k<<=1){
            sort(SA,SA+n,cmp);
            invSA[0]=0;
            for(i=1; i<n; i++)invSA[i]=invSA[i-1]+cmp(SA[i-1],SA[i]);
            for(i=0; i<n; i++)RA[SA[i]]=invSA[i];
            if(invSA[n-1]==n-1)break;
        }
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
		lgval[0]=lgval[1]=0;
		for(int i=2; i<N; i++)lgval[i]=lgval[i>>1]+1;
        for(i=1; i<=K; i++){
            for(j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }
    inline int lcp(int i, int j){
        int lg =lgval[j-i+1];
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
}SA;

int mark[500005];
int len[500005];

void solve(int casenum){
	vector<int>s;
	string tmp;
	int x;
	cin>>x;
	int ch=1000;
	for(int i=0; i<x; i++){
		cin>>tmp;
		mark[i]=(int)s.size();
		len[i]=(int)tmp.size();
		for(char c:tmp)s.push_back((int)c);
		s.push_back(ch++);
	}
	
	SA.init(s);
	int q,l,r,L,low,high,mid,upper,lower,cur;
	cin>>q;
	while(q--){
		cin>>l>>r;
		l--,r--;
		cur=len[l];
		
		l=SA.invSA[mark[l]];
		r=SA.invSA[mark[r]];
		if(l>r)swap(l,r);
		if(l!=r)L=SA.lcp(l+1,r);
		else L=cur;
		
		if(L==0)cout<<0<<'\n';
		else{
			low=0,high=l-1,mid,lower=l;
			while(low<=high){
				mid = (low+high)>>1;
				if(SA.lcp(mid+1,l)>=L){
					lower=min(lower,mid);
					high=mid-1;
				}
				else low=mid+1;
			}
			
			low=r+1,high=sz(s),upper=r;
			while(low<=high){
				mid=(low+high)>>1;
				if(SA.lcp(r+1,mid)>=L){
					upper=max(upper,mid);
					low=mid+1;
				}
				else high=mid-1;
			}
			cout<<upper-lower+1<<'\n';
		}
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