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

const int N = 1e5+5;

const int K=__lg(N)+1;
struct SuffixArray{
    int SA[N],LCP[N]={0},invSA[N];
    int RA[N],c[N],n;
    int Table[K][N]={{0}},lgval[N];
    inline void countingSort(int k){
        int mx = max(130,n),i,j,sum;
		fill(c,c+mx+1,0);
		for(i=0; i<n; i++)c[i+k<n ? RA[i+k]:0]++;
		for(i=0,sum=0; i<mx; i++){j=c[i],c[i]=sum,sum+=j;}
		for(i=0; i<n; i++)invSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];
		for(i=0; i<n; i++)SA[i]=invSA[i];
    }
    void init(const string &s){
        int i,k,j;
		n = (int)s.size();
		auto cmp = [&](int &a, int &b)->bool{
			if(RA[a]^RA[b])return RA[a]<RA[b];
			return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
		};
        for(i=0; i<n; i++)SA[i]=i,RA[i]=s[i];
		for(k=1; k<n; k<<=1){
			countingSort(k);
			countingSort(0);
			invSA[0]=1;
			for(i=1; i<n; i++)invSA[i]=invSA[i-1]+cmp(SA[i-1],SA[i]);
			for(i=0; i<n; i++)RA[SA[i]]=invSA[i];
			if(invSA[n-1]==n)break;
		}
		for(i=0; i<n; i++)invSA[SA[i]]=i;
		for(i=0,k=0; i<n; i++){
			if(invSA[i]==0)k=0;
			else{
				j=SA[invSA[i]-1];
				while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;
				LCP[invSA[i]]=k;
				Table[0][invSA[i]]=k;
				if(k>0)k--;
				else k=0;
			}
		}
		//for(i=0; i<n; i++)cerr<<setw(2)<<SA[i]<<", LCP: "<<LCP[i]<<" "<<s.substr(SA[i])<<endl;
        for(i=1; i<=K; i++){
            for(j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
    }

     inline int lcp(int l, int r){
        int lg=lgval[r-l+1];
        return min(Table[lg][l],Table[lg][r-(1<<lg)+1]);
    }
}SA;



void solve(int casenum){
	string s;
	cin>>s;
	SA.init(s);
	int n = sz(s);
	
	vector<int>diff(n+1,0);
	
	ll ans=0;
	int cnt=0,offset=0;
	for(int i=0,low,high,mid,cur,L; i<n; i++){
		offset+=diff[i];
		do{
			low=i+1,high=n-1,cur=-1;
			while(low<=high){
				mid = (low+high)>>1;
				if((SA.lcp(i+1,mid)-offset)>0){
					low=mid+1;
					cur=max(cur,mid);
				}
				else high=mid-1;
			}
			if(cur==-1)break;
			L = SA.lcp(i+1,cur)-offset;
			cnt = cur-i+1;
			ans+=1LL*cnt*cnt*L;
			offset+=L;
			diff[cur+1]-=L;
		}while(cur!=-1);
		ans+=(n-SA.SA[i]-offset);
	}
	cout<<ans<<endl;
}

int main(){
	SA.lgval[0]=SA.lgval[1]=0;
	for(int i=2; i<N; i++)SA.lgval[i]=SA.lgval[i>>1]+1;
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}