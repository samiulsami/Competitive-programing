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

const int N = 2e5+5;

int arr[N];

struct msSum{
	set<pii>ms;
	ll sum=0;
	msSum(){}
	bool empty(){return ms.empty();}
	pii front(){return *ms.begin();}
	pii back(){return *ms.rbegin();}
	int size(){return ms.size();}
	
	void erase(pii x){
		ms.erase(ms.find(x));
		sum-=x[0];
	}
	
	void insert(pii x){
		ms.insert(x);
		sum+=x[0];
	}
	
	int count(pii x){
		return ms.count(x);
	}
};

void solve(int casenum){
	int n,k;
	sf("%d%d",&n,&k);
	
	for(int i=1; i<=n; i++)sf("%d",&arr[i]);
	msSum L,R;
	
	auto balance = [&]()->void{
		if(L.size()>R.size()+1){
			R.insert(L.back());
			L.erase(L.back());
		}
		if(R.size()>L.size()){
			L.insert(R.front());
			R.erase(R.front());
		}
	};
	
	for(int i=1; i<=n; i++){
		if(L.empty() || L.back()[0]>arr[i])L.insert({arr[i],i});
		else R.insert({arr[i],i});
		
		balance();
		
		if(L.size()+R.size()==k){
			ll lesserEqual = L.sum;
			ll lesserEqualCount = L.size();
			ll greater = R.sum;
			ll greaterCount = R.size();
			ll median = L.back()[0];
			
			ll ans = lesserEqualCount*median - lesserEqual + greater - median*greaterCount;
			pf("%lld ",ans);
			pii x{arr[i-k+1],i-k+1};
			
			if(L.count(x))L.erase(x);
			else R.erase(x);
			
			balance();
		}
	}
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