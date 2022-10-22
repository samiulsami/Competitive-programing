#include<bits/stdc++.h>
using namespace std;
///https://codeforces.com/gym/103483/problem/I
typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;
const int B = rand(500,1<<20);
const int MOD = 1e9+7;
int _pow[1000006];
string strings[100005];

bool f(vector<int>s, int mask){
	if(sz(s)<=1)return 1;
	int tmpmask = (1<<26)-1;
	
	for(int i:s){
		string &x = strings[i];
		int tmptmpmask=0;
		for(char c:x)tmptmpmask|=(1<<(c-'a'));
		tmpmask&=tmptmpmask;
	}
	
	char cur='A';
	int newmask=mask;
	for(int i=0; i<27; i++){
		if(bool(tmpmask&(1<<i)) && !bool(mask&(1<<i))){
			cur = char(i+'a');
			newmask|=(1<<i);
			break;
		}
	}
	
	if(cur=='A')return 0;
	map<int,vector<int> >_hashes;
	
	for(int i:s){
		string &x = strings[i];
		int curhash=0;
		for(int j=0; j<x.length(); j++){
			if(x[j]==cur){
				curhash = (1LL*curhash + (1LL*_pow[j]*ll(cur))%MOD)%MOD;
			}
		}
		_hashes[curhash].push_back(i);
	}
	
	bool possible=1;
	for(auto &it:_hashes)
		possible&=f(it.second,newmask);
	
	return possible;
}

inline void solve(int caseNum){
	int l,n;
	cin>>l>>n;
	vector<int>arr(n);
	for(int i=0; i<n; i++)cin>>strings[i],arr[i]=i;
	if(f(arr,0))cout<<"YES\n";
	else cout<<"NO\n";
}

int main(){
	_pow[0]=1;
	for(int i=1; i<=1000001; i++)_pow[i] = (1LL*B*_pow[i-1])%MOD;
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}