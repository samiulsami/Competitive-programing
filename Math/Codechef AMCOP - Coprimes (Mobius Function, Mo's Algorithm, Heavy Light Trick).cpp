#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()

const int N = 1e5+5;
const int MOD = 1e9+7;
const int DIV = 300;
const int Div2 = 600;
int mu[N];
int fact[N];
int invFact[N];

int bigMod(int a, int b){
	int ret=1;
	while(b){
		if(b&1)ret = (1LL*ret*a)%MOD;
		b>>=1;
		a = (1LL*a*a)%MOD;
	}
	return ret;
}

inline int ncr(int n, int r){
	if(n<r)return 0;
	return ((1LL*fact[n]*invFact[r])%MOD * 1LL*invFact[n-r])%MOD;
}

inline void mobius(){
	///mu[1] = 1;
	///mu[x] = 0 if x is divisible by a^2 where 'a' is a prime
	///mu[x] = (-1)^k if 'x' is the product of 'k' distinct primes
	for(int i=0; i<N; i++)mu[i]=2;
	mu[1]=1;
	for(int i=2; i<N; i++){
		if(mu[i]==2){
			mu[i]=-1;
			if(i<=N/i){
				int x=i*i;
				for(int j=x; j<N; j+=x)mu[j]=0;
			}
			for(int j=i+i; j<N; j+=i){
				if(mu[j]==2)mu[j]=-1;
				else mu[j]*=-1;
			}
		}
	}
}

vector<int>divisors[N];
int arr[50005];

struct query{
	int l,r,k,x,i;
	bool operator<(const query &q)const{
		if(x^q.x)return x<q.x;
		return (x&1)?r<q.r:r>q.r;
	}
}queries[50005];
int ans[50005]={0};

int muSum[100005]={0};
int cnt[100005]={0};
int cntOcc[100005]={0};
set<int>st;

void add(int x){
	for(int d:divisors[arr[x]]){
		muSum[cnt[d]] -= mu[d];
		cntOcc[cnt[d]]--;
		if(cnt[d]>Div2 && cntOcc[cnt[d]]==0)st.erase(cnt[d]);
		cnt[d]++;
		muSum[cnt[d]] += mu[d];
		cntOcc[cnt[d]]++;
		if(cnt[d]>Div2 && cntOcc[cnt[d]]==1)st.insert(cnt[d]);
	}
}

void rem(int x){
	for(int d:divisors[arr[x]]){
		muSum[cnt[d]] -= mu[d];
		cntOcc[cnt[d]]--;
		if(cnt[d]>Div2 && cntOcc[cnt[d]]==0)st.erase(cnt[d]);
		cnt[d]--;
		muSum[cnt[d]] += mu[d];
		cntOcc[cnt[d]]++;
		if(cnt[d]>Div2 && cntOcc[cnt[d]]==1)st.insert(cnt[d]);
	}
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	mobius();
	fact[0]=1;
	for(int i=1; i<N; i++){
		fact[i] = (1LL*i*fact[i-1])%MOD;
		if(mu[i]==0)continue;
		for(int j=i; j<N; j+=i)
			divisors[j].push_back(i);
	}
	
	invFact[N-1] = bigMod(fact[N-1],MOD-2);
	for(int i=N-1; i>0; i--)invFact[i-1] = (1LL*invFact[i]*i)%MOD;
	
	int n,q;
	cin>>n;
	for(int i=1; i<=n; i++)cin>>arr[i];
	
	cin>>q;
	for(int i=1,a,b,c; i<=q; i++){
		cin>>a>>b>>c;
		queries[i] = {a,b,c,a/DIV,i};
	}
	sort(queries+1, queries+q+1);
	
	int l=1,r=0;
	for(int i=1; i<=q; i++){
		while(queries[i].r>r)add(++r);
		while(queries[i].l<l)add(--l);
		while(queries[i].r<r)rem(r--);
		while(queries[i].l>l)rem(l++);
		
		int &tmp = ans[queries[i].i];
		for(int x=1; x<=Div2; x++)tmp = (tmp + (1LL*ncr(x,queries[i].k)*muSum[x])%MOD + MOD)%MOD;
		for(int x:st){
			tmp = (tmp + (1LL*ncr(x,queries[i].k)*muSum[x])%MOD + MOD)%MOD;
		}
	}
	
	for(int i=1; i<=q; i++){
		cout<<(ans[i]+MOD)%MOD<<"\n";
	}
return 0;
}