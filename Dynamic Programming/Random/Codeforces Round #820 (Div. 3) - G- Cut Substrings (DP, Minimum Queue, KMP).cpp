#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int MOD = 1e9+7;

template<typename T>
struct minQueue{
	stack<pair<T,T> >A,B;
	minQueue(){}
	T Combine(const T &a, const T &b){
		if(a[1]!=b[1]){
			T ret;
			ret[0] = max(a[0],b[0]);
			if(a[1]<b[1]){
				ret[1] = a[1];
				ret[2] = a[2];
			}
			else{
				ret[1] = b[1];
				ret[2] = b[2];
			}
			return ret;
		}
		
		return {max(a[0],b[0]), a[1], (a[2]+b[2])%MOD};
	}

	void push(T x){
		T y = A.empty()?x:Combine(x,A.top().second);
		A.push({x,y});
	}
	void work(){
		if(B.empty()){
			while(!A.empty()){
				T x=A.top().first;
				A.pop();
				T y = B.empty()?x:Combine(x,B.top().second);
				B.push({x,y});
			}
		}
	}
	T pop(){
		work();
		T ret=B.top().first;
		B.pop();
		return ret;
	}
	T front(){
		work();
		return B.top().first;
	}
	T get(){
		if(A.empty())return B.top().second;
		if(B.empty())return A.top().second;
		return Combine(A.top().second, B.top().second);
	}
	bool empty(){return A.empty() && B.empty();}
	int size(){return A.size() + B.size();}
};

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
	vector<pii(2)>dp(n+1);
	
	auto pi = kmp(t);
	for(int i=0,j=0; i<n; i++){
		while(j && s[i]!=t[j])j = pi[j-1];
		if(s[i]==t[j])j++;
		if(j==sz(t)){
			mark[i-j+1]=1;
			j = pi[j-1];
		}
	}

	minQueue<pii(3)>q; //{last index, min element, count}
	dp[n]={0,1};
	
	for(int i=n-1; i>=0; i--){
		if(!mark[i]){
			dp[i] = dp[i+1];
			continue;
		}

		while(!q.empty() && (q.get()[0] > i+2*sz(t)-1))q.pop();
		if(i+sz(t)<=n)q.push({i+sz(t), dp[i+sz(t)][0], dp[i+sz(t)][1]});
		
		auto cur = q.get();
		dp[i] = {cur[1], cur[2]};
		dp[i][0]++;
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