#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int MOD = 1e9+7;
const int N = 505;

struct segtree{
	#define T pii(2)
	T Tree[4*N];

	inline T Combine(T a, T b){
		if(a[0]!=b[0])return min(a,b);
		int x = a[1]+b[1];
		if(x>=MOD)x-=MOD;
		return {a[0],x};
	}

	void build(int node, int l, int r){
		Tree[node] = {550,0};
		if(l^r){
			int mid = (l+r)>>1;
			build(node<<1,l,mid);
			build(node<<1|1,mid+1,r);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	void update(int node, int l, int r, int pos, T val){
		if(l==pos && r==pos)Tree[node]=val;
		else{
			int mid = (l+r)>>1;
			if(pos<=mid)update(node<<1,l,mid,pos,val);
			else update(node<<1|1,mid+1,r,pos,val);
			Tree[node] = Combine(Tree[node<<1],Tree[node<<1|1]);
		}
	}

	T query(int node, int l, int r, int posl, int posr){
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}
	
	#undef T
}st;

vector<int> kmp(const string &s){
    vector<int>pi((int)s.size(),0);
    for(int i=1,j=0; i<(int)s.size(); i++){
        j=pi[i-1];
        while(j && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
    }
    return pi;
}

inline void solve(int caseNum){
	string s,t;
	cin>>s>>t;
	int n = s.length();
	vector<bool>mark(n,0);
	vector<pii(2)>dp(n+2);
	
	auto pi = kmp(t);
	for(int i=0,j=0; i<n; i++){
		while(j && s[i]!=t[j])j = pi[j-1];
		if(s[i]==t[j])j++;
		if(j==sz(t)){
			mark[i-j+1]=1;
			j = pi[j-1];
		}
	}

	st.build(1,0,n);

	dp[n]={0,1};
	if(n-sz(t)>=0 && mark[n-sz(t)])st.update(1,0,n,n,dp[n]);
	
	for(int i=n-1; i>=0; i--){
		if(!mark[i]){
			dp[i] = dp[i+1];
			if(i-sz(t)>=0 && mark[i-sz(t)])st.update(1,0,n,i, dp[i]);
			continue;
		}
		// auto &cur = dp[i];
		// cur = {550,0};
		// for(int k=0; k<t.length() && i+k+t.length()-1 < n; k++){
		// 	if(!mark[i+k])continue;
		// 	auto nxt = dp[i+k+t.length()];
		// 	nxt[0]++;
		// 	if(nxt[0] < cur[0])cur = nxt;
		// 	else if(nxt[0]==cur[0]){
		// 		cur[1] += nxt[1];
		// 		if(cur[1]>=MOD)cur[1]-=MOD;
		// 	}
		// }
		assert(i+sz(t)<=n);
		dp[i] = st.query(1,0,n,i+sz(t), min(n, i+2*sz(t)-1));
		dp[i][0]++;
		if(i-sz(t)>=0 && mark[i-sz(t)])st.update(1,0,n,i, dp[i]);
	}

	cout<<dp[0][0]<<" "<<dp[0][1]<<"\n";
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}