#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl;
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
const int N = 1e5+5;

const int K=__lg(N)+1;
struct SuffixArray{
    int SA[N],LCP[N],invSA[N];
    int RA[N],c[N],n;
    int Table[K][N]={{0}};
    inline void countingSort(int k){
        int i, sum, maxi = max(300, n),t;
        memset(c, 0, sizeof c);
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
    }

    inline int lcp(int i, int j){
		if(i>j)swap(i,j);
		i++;
        int lg = __lg(j-i+1);
        return min(Table[lg][i], Table[lg][j-(1<<lg)+1]);
    }
}SA;
////aaababbaa
string s;

const int INF=1e9;

pii Tree[2*N];
int n;

inline pii Merge(pii a, pii b){return pii(max(a.first,b.first),min(a.second,b.second));}

void update(int ind){
    ind+=n-1;
    Tree[ind]=pii(ind-n+1,ind-n+1);
    for(;ind>1; ind>>=1)Tree[ind>>1] = Merge(Tree[ind],Tree[ind^1]);
}

pii query(int l, int r){ ///[l,r]
    l+=n-1;
    r+=n;
    pii ret(-INF,INF);
    for(;l<r; l>>=1,r>>=1){
        if(l&1)ret=Merge(ret,Tree[l++]);
        if(r&1)ret=Merge(ret,Tree[--r]);
    }
    return ret;
}


void solve(int caseno){
    cin>>s;
	reverse(all(s));
	s+="$";
    SA.init(s);
	n = sz(s);
	for(int i=0; i<=2*n; i++)Tree[i]=pii(-INF,INF);
	ll ans=0;
	for(int i=n-2; i>=0; i--){
		int cur=0;
		
		int l = query(1,SA.invSA[i]).first;
		int r = query(SA.invSA[i],n).second;
		
		if(l!=-INF)cur=max(cur,SA.lcp(SA.invSA[i],l));
		if(r!=INF)cur=max(cur,SA.lcp(SA.invSA[i],r));
		
		//pf("%d %d\n",l,r);
		ans+=n-i-cur-1;
		update(SA.invSA[i]);
		cout<<ans<<endl;
	}
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}