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


int arr[N],n;
int Table[20][N];
ll TableSum[20][N]={0};
ll pSum[N]={0};

inline ll getsum(int l, int r){
	if(l>r)return 0;
	ll ret = pSum[r];
	if(l>0)ret-=pSum[l-1];
	return ret;
}

void solve(int casenum){
	int q;
	sf("%d%d",&n,&q);
	for(int i=0; i<n; i++){
		sf("%d",&arr[i]);
		pSum[i]=arr[i];
		if(i)pSum[i]+=pSum[i-1];
	}
	
	arr[n]=int(2e9);
	stack<int>st;
	st.push(n);
	
	for(int i=n-1; i>=0; i--){
		while(arr[st.top()]<arr[i])st.pop();
		int j=st.top();
		Table[0][i]=j;
		ll sum = 1LL*(j-i)*arr[i] - getsum(i,j-1)*1LL;
		
		TableSum[0][i] = sum;
		st.push(i);
	}
	
	for(int k=1; k<19; k++){
		for(int i=0; i<n; i++){
			if(Table[k-1][i]==n){
				Table[k][i]=n;
				TableSum[k][i]=TableSum[k-1][i];
			}
			else {
				Table[k][i] = Table[k-1][Table[k-1][i]];
				TableSum[k][i] = TableSum[k-1][i] + TableSum[k-1][Table[k-1][i]];
			}
		}
	}
	
	int l,r;
	while(q--){
		sf("%d%d",&l,&r);
		if(l==r){
			pf("0\n");
			continue;
		}
		
		l--,r--;
		ll ans=0;
		for(int k=18; k>=0; k--){
			if(Table[k][l]<=r){
				ans+=TableSum[k][l];
				l=Table[k][l];
			}
		}
		
		if(l<r){
			ans+= 1LL*arr[l]*(r-l+1) - getsum(l,r);
		}
		pf("%lld\n",ans);
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