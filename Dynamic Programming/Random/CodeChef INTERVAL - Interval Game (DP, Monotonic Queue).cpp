#include<bits/stdc++.h>
using namespace std;
// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 3e5+5;
const ll INF = 1e18;

template<typename T>
struct minQueue{
	deque<pair<T,int> >q;
	int cnt_added=0;
	int cnt_removed=0;
	minQueue(){}
	void push(T x){
		while(!q.empty() && q.back().first>x)q.pop_back();
		q.push_back({x,cnt_added});
		cnt_added++;
	}
	void pop(){
		if (!q.empty() && q.front().second == cnt_removed) 
    	q.pop_front();
		cnt_removed++;
	}
	T getMin(){
		return q.front().first;
	}
	bool empty(){return q.empty();}
	int size(){return cnt_added-cnt_removed;}
};

template<typename T>
struct maxQueue{
	deque<pair<T,int> >q;
	int cnt_added=0;
	int cnt_removed=0;
	maxQueue(){}
	void push(T x){
		while(!q.empty() && q.back().first<x)q.pop_back();
		q.push_back({x,cnt_added});
		cnt_added++;
	}
	void pop(){
		if(!q.empty() && q.front().second == cnt_removed)q.pop_front();
		cnt_removed++;
	}
	T getMin(){
		return q.front().first;
	}
	bool empty(){return q.empty();}
	int size(){return cnt_added-cnt_removed;}
};

ll dp[2][N];
ll A[N];
int B[201];

inline void solve(int caseNum){
	int n,m;
	scanf("%d%d",&n,&m);

	for(int i=0,x; i<n; i++){
		scanf("%d",&x);
		A[i]=x;
		if(i)A[i]+=A[i-1];
	}

	for(int i=0; i<m; i++){
		scanf("%d",&B[i]);
	}

	
	for(int i=0; i<n; i++){
		dp[0][i] = -INF;
		dp[1][i] = -INF;
	}

	bool flag=1;	///true if chef's turn.
	if(m%2==0)flag=0;

	for(int i=0; i+B[m-1]-1<n; i++){
		ll cur = A[i+B[m-1]-1];
		if(i)cur-=A[i-1];
		if(!flag)cur = -cur;
		dp[flag][i] = cur;
	}

	flag^=1;

	for(int j=m-2; j>=0; j--){
		for(int i=0; i<n; i++)dp[flag][i] = -INF;
		if(flag){
			minQueue<ll>mq;

			for(int i=n-1; i>=0; i--){
				if((i+B[j+1]-1) >= n)continue;
				while(sz(mq)>(B[j]-B[j+1]-1))mq.pop();

				if(!mq.empty() && (i+B[j]-1)<n){
					ll cur = A[i+B[j]-1];
					if(i)cur -= A[i-1];
					ll tmp = mq.getMin();
					dp[flag][i] = cur+tmp;
				}
				mq.push(dp[flag^1][i]);
			}
		}
		else{
			maxQueue<ll>mq;
			for(int i=n-1; i>=0; i--){
				if((i+B[j+1]-1) >= n)continue;
				while(sz(mq)>(B[j]-B[j+1]-1))mq.pop();

				if(!mq.empty() && (i+B[j]-1)<n){
					ll cur = A[i+B[j]-1];
					if(i)cur -= A[i-1];
					cur = -cur;
					ll tmp = mq.getMin();
					dp[flag][i] = cur+tmp;
				}

				mq.push(dp[flag^1][i]);
			}
		}
		flag^=1;
	}
	
	ll mx = -INF;
	for(int i=0; i<n; i++)mx = max(mx, dp[flag^1][i]);
	printf("%lld\n",mx);
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	//ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	scanf("%d",&T);
	for(int i=1; i<=T; i++)solve(i);
return 0;
}