#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef long double ld;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<"\n"
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 5e5+5;
const int K = 800;


struct query{
	int l,r,ind,x;
	bool operator<(const query &q)const{
		if(x^q.x)return l<q.l;
		return (x&1)?r<q.r:r>q.r;
	}
}queries[N];

int ans[N];
int arr[N];
int exists[K+5]={0};
int singletons=0;
int cnt[N]={0};
int l=0,r=-1;

inline void add(int i){
	if(++cnt[arr[i]]==1)exists[arr[i]/K]++,singletons++;
	else if(cnt[arr[i]]==2)exists[arr[i]/K]--,singletons--;
}

inline void rem(int i){
	if(--cnt[arr[i]]==0)exists[arr[i]/K]--,singletons--;
	else if(cnt[arr[i]]==1)exists[arr[i]/K]++,singletons++;
}

inline int getAns(){
	if(singletons==0)return -1;
	int i=0;
	for(; !exists[i] && i<=K; i++);
	
	i*=K;
	for(;cnt[i]!=1;i++);
	return i;
}

void solve(int casenum){
	int n;
	sf("%d",&n);
	
	for(int i=0; i<n; i++){
		sf("%d",&arr[i]);
		arr[i]--;
	}
	
	int q;
	sf("%d",&q);
	for(int i=0,l,r; i<q; i++){
		sf("%d%d",&l,&r);
		queries[i] = {l-1,r-1,i,l/K};
	}
	sort(queries,queries+q);
	
	for(int i=0; i<q; i++){
		while(l>queries[i].l)add(--l);
		while(r<queries[i].r)add(++r);
		while(l<queries[i].l)rem(l++);
		while(r>queries[i].r)rem(r--);
		
		ans[queries[i].ind] = getAns()+1;
	}
	
	for(int i=0; i<q; i++)pf("%d\n",ans[i]);
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}