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

const int N = 1e5+40;

const int K=__lg(N)+1;
struct SuffixArray{
    int SA[N],LCP[N],invSA[N];
    int RA[N],c[N],n;
    int Table[K][N]={{0}};
	int lgval[N];
    inline void countingSort(int k){
        int i, sum, maxi = max(130, n),t;
        fill(c,c+maxi+1,0);
        for (i = 0; i < n; i++)c[i + k < n ? RA[i + k] : 0]++;
        for (i = sum = 0; i < maxi; i++){t = c[i]; c[i] = sum; sum += t;}
        for (i = 0; i < n; i++)invSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        for (i = 0; i < n; i++)SA[i] = invSA[i];
    }
    void init(const string &s){
        int i,k,j,r;
        n=(int)s.size();
        for (i = 0; i < n; i++)RA[i]=s[i],SA[i]=i;
        for (k = 1; k < n; k <<= 1){
            countingSort(k);
            countingSort(0);
            invSA[SA[0]] = r = 0;
            for (i = 1; i < n; i++)invSA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
            for (i = 0; i < n; i++)RA[i] = invSA[i];
            if (RA[SA[n-1]] == n-1) break;
        }
        for(i=0; i<n; i++) invSA[SA[i]]=i;
        for(i=0,k=0; i<n; i++, k?k--:0){
            if(invSA[i]==0){k=0; continue;}
            j=SA[invSA[i]-1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            LCP[invSA[i]]=k;
            Table[0][invSA[i]]=k;
        }
        for(i=1; i<=K; i++){
            for(j=0; j+(1<<i)-1<n; j++){
                Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
            }
        }
		lgval[0]=lgval[1]=0;
		for(int i=2; i<N; i++)lgval[i]=lgval[i>>1]+1;
    }

    inline int lcp(int i, int j){
        int lg = lgval[j-i+1];
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
}SA;

int mark[N];
int counter[12]={0};

void solve(int casenum){
	string t,s;
	char ch=2;
	int len=0,cnt=0;
	int k;
	cin>>k;
	for(int i=0; i<k; i++){
		cin>>t;
		t+=ch;
		s+=t;
		for(int i=0; i<sz(t); i++){
			mark[i+len]=cnt;
		}
		//if(len>0)mark[len-1]=cnt;
		cnt++;
		ch++;
		len+=sz(t);
	}
	//for(int i=0; i<len; i++)cout<<s[i]<<" "<<mark[i]<<endl;
	SA.init(s);
	fill(counter,counter+10,0);
	int l=0,ans=0,inrange=0;
	for(int i=0; i<len; i++){
		if(++counter[mark[SA.SA[i]]]==1)inrange++;
		while(l<i && inrange==cnt){
			ans=max(ans,SA.lcp(l+1,i));
			if(--counter[mark[SA.SA[l++]]]==0)inrange--;
		}
	}
	cout<<ans<<endl;
}

int main(){
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