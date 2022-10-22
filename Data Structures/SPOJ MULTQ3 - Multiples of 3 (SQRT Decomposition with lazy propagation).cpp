#include<bits/stdc++.h>
using namespace std;
 
typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
 
const int N = 1e5+5;
const int K = 320;
int n;
int arr[N];
int Block[3][K]={0};
int lazy[K]={0};
 
inline void recalc(int b){
	//if(lazy[b]==0)return;
	int l = b*K, r = min(n,(b+1)*K);
	Block[0][b]=0;
	Block[1][b]=0;
	Block[2][b]=0;
 
	for(int i=l; i<r; i++){
		arr[i] += lazy[b];
		if(arr[i]>=3)arr[i]-=3;
		Block[arr[i]][b]++;
	}
	lazy[b]=0;
}
 
void update(int l, int r){
	int L=l/K,R=r/K;
	if(L==R){
		for(;l<=r; l++)if(++arr[l]>=3)arr[l]-=3;
		recalc(L);
		return;
	}	
 
	for(int i=l,mx=(L+1)*K; i<mx; i++)if(++arr[i]>=3)arr[i]-=3;
	recalc(L);
	for(int i=R*K; i<=r; i++)if(++arr[i]>=3)arr[i]-=3;
	recalc(R);
	
	for(int i=L+1,tmp; i<R; i++){
		lazy[i]++;
		tmp = Block[2][i];
		Block[2][i] = Block[1][i];
		Block[1][i] = Block[0][i];
		Block[0][i] = tmp;
		if(lazy[i]>=3)lazy[i]-=3;
	}
}
 
int query(int l, int r){
	int L=l/K,R=r/K;
 
	if(L==R){
		int ret=0;
		if(lazy[L])recalc(L);
		for(;l<=r; l++)ret += (arr[l]==0);
		return ret;
	}	
	int ret=0;
 
	if(lazy[L])recalc(L);
	for(int i=l,mx=(L+1)*K; i<mx; i++)ret += (arr[i]==0);
	if(lazy[R])recalc(R);
	for(int i=R*K; i<=r; i++)ret += (arr[i]==0);
	for(int i=L+1; i<R; i++)ret += Block[0][i];
 
	return ret;
}
 
inline void solve(int caseNum){
	int q;
	cin>>n>>q;
	for(int i=0; i<n; i++){
		arr[i]=0;
		Block[0][i/K]++;
	}
 
	int a,l,r;
	while(q--){
		cin>>a>>l>>r;
		if(a==0)update(l,r);
		else cout<<query(l,r)<<"\n";
	}
 
}
 
int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
} 