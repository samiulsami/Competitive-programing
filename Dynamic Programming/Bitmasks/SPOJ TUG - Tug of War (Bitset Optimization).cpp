#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;
bitset<10001>bs;
int arr[N];

inline void solve(int caseNum){
	int n;
	cin>>n;
	for(int i=0; i<n; i++)cin>>arr[i];
	
	if(n>100){
		cout<<"YES\n";
		return;
	}
	
	bs.reset();
	bs[0]=1;
	for(int i=0; i<n; i++){
		if((bs&(bs<<arr[i])).count()){
			cout<<"YES\n";
			return;
		}
		bs|=(bs<<arr[i]);
	}
	cout<<"NO\n";
}

int main(){
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}