#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;
const int DIV = 400;

deque<int>Block[DIV];
int cnt[DIV][N]={0};


int getCnt(int l, int r, int k){
	int ret=0;
	int ll=l/DIV, rr = r/DIV;
	if(ll==rr){
		stack<int>stLeft;
		int lft = l-(ll*DIV);
		while(lft--){
			stLeft.push(Block[ll].front());
			Block[ll].pop_front();
		}
		
		lft = r-l+1;
		while(lft--){
			stLeft.push(Block[ll].front());
			Block[ll].pop_front();
			if(stLeft.top()==k)ret++;
		}
		while(!stLeft.empty()){
			Block[ll].push_front(stLeft.top());
			stLeft.pop();
		}
		return ret;
	}
	
	int cntLeft = (ll+1)*DIV - l;
	stack<int>st;
	while(cntLeft--){
		st.push(Block[ll].back());
		Block[ll].pop_back();
		if(st.top()==k)ret++;
	}
	while(!st.empty()){
		Block[ll].push_back(st.top());
		st.pop();
	}
	
	int cntRight = r-(rr*DIV)+1;
	while(cntRight--){
		st.push(Block[rr].front());
		Block[rr].pop_front();
		if(st.top()==k)ret++;
	}
	while(!st.empty()){
		Block[rr].push_front(st.top());
		st.pop();
	}
	
	for(int i=ll+1; i<rr; i++)ret+=cnt[i][k];
	return ret;
}

void cyclic_shift(int l, int r){
	int ll = l/DIV, rr = r/DIV;
	
	if(ll==rr){
		stack<int>stLeft,stMiddle;
		int cntleft = l-(ll*DIV);
		while(cntleft--){
			stLeft.push(Block[ll].front());
			Block[ll].pop_front();
		}
		
		int last=-1;
		int cntMiddle = r-l+1;
		while(cntMiddle--){
			stMiddle.push(Block[ll].front());
			Block[ll].pop_front();
			last=stMiddle.top();
		}
		stMiddle.pop();
		stLeft.push(last);
		
		while(!stMiddle.empty()){
			Block[ll].push_front(stMiddle.top());
			stMiddle.pop();
		}
		while(!stLeft.empty()){
			Block[ll].push_front(stLeft.top());
			stLeft.pop();
		}
	}
	// else if(ll+1 == rr){
		// int last;
		// stack<int>stRight;
		// int cntRight = r-(rr*DIV)+1;
		// while(cntRight--){
			// stRight.push(Block[rr].front());
			// Block[rr].pop_front();
		// }
		// last=stRight.top();
		// stRight.pop();
		// while(!stRight.empty()){
			// Block[rr].push_front(stRight.top());
			// stRight.pop();
		// }
		
		// Block[rr].push_front(Block[ll].back());
		// Block[ll].pop_back();
		
		// int cntLeft = (ll+1)*DIV - l - 1;
		// while(cntLeft--){
			// stRight.push(Block[ll].back());
			// Block[ll].pop_back();
		// }
		
		// stRight.push(last);
		// while(!stRight.empty()){
			// Block[ll].push_back(stRight.top());
			// stRight.pop();
		// }
	// }
	else{
		for(int i=ll+1,x; i<=rr; i++){
			x = Block[i-1].back();
			Block[i].push_front(x);
			Block[i-1].pop_back();
			cnt[i][x]++;
			cnt[i-1][x]--;
		}
		
		stack<int>stRight;
		int cntRight = r-(rr*DIV)+2;
		int last;
		while(cntRight--){
			stRight.push(Block[rr].front());
			Block[rr].pop_front();
		}
		last=stRight.top();
		stRight.pop();
		
		while(!stRight.empty()){
			Block[rr].push_front(stRight.top());
			stRight.pop();
		}
		
		int cntLeft = (ll+1)*DIV - l - 1;
		
		while(cntLeft--){
			stRight.push(Block[ll].back());
			Block[ll].pop_back();
		}
		stRight.push(last);
		cnt[ll][last]++;
		cnt[rr][last]--;
		
		while(!stRight.empty()){
			Block[ll].push_back(stRight.top());
			stRight.pop();
		}
	}
}

void solve(int casenum){
	int n,x,q,qt,l,r,ans,k;
	si(n);
	FOR(i,n){
		si(x);
		Block[i/DIV].push_back(x);
		cnt[i/DIV][x]++;
	}
	
	ans=0;
	si(q);
	while(q--){
		siii(qt,l,r);
		//l--,r--;
		l = (l+ans-1)%n;
		r = (r+ans-1)%n;
		if(l>r)swap(l,r);
		if(qt==1)cyclic_shift(l,r);
		else{
			si(k);
			k = (k+ans-1)%n + 1;
			ans = getCnt(l,r,k);
			//pf("l, r, k: %d %d %d\n",l,r,k);
			pf("%d\n",ans);
		}
	}
	
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}