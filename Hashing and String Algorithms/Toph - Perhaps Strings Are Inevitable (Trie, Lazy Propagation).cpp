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


struct trieNode{
	trieNode *nxt[26];
	int cnt;
	trieNode *lazy;
	trieNode(){
		for(int i=0; i<26; i++)nxt[i]=NULL;
		cnt=0;
		lazy=NULL;
	}
	bool check(trieNode *cur){
		return cur && cur->cnt>0;
	}
	void push_lazy(){
		if(lazy){
			lazy->push_lazy();
			cnt+=lazy->cnt;
			for(int i=0; i<26; i++){
				if(check(lazy->nxt[i]) && !check(nxt[i]))nxt[i]=lazy->nxt[i];
				else if(!check(lazy->nxt[i]) && check(nxt[i])){
					
				}
				else if(check(lazy->nxt[i]) && check(nxt[i])){
					nxt[i]->push_lazy();
					nxt[i]->lazy = lazy->nxt[i];
				}
				if(nxt[i])nxt[i]->push_lazy();
			}
			lazy=NULL;
		}
	}
}*root;

void insert(string &s){
	trieNode *cur=root;
	for(char &c:s){
		if(!cur->nxt[c-'a'])cur->nxt[c-'a'] = new trieNode();
		cur = cur->nxt[c-'a'];
		cur->cnt++;
	}
}

int query(const string &s){
	trieNode *cur=root;
	for(char c:s){
		cur->push_lazy();
		if(!cur->nxt[c-'a'] || cur->nxt[c-'a']->cnt<=0)return 0;
		cur = cur->nxt[c-'a'];
	}
	cur->push_lazy();
	return cur->cnt;
}

void update(const string &s, char x){
	trieNode *cur=root;
	trieNode *prev=NULL;
	char lastChar='0';
	for(char c:s){
		cur->push_lazy();
		if(!cur->nxt[c-'a'] || cur->nxt[c-'a']->cnt<=0)return;
		prev=cur;
		cur = cur->nxt[c-'a'];
		lastChar=c;
	}
	cur->push_lazy();
	if(lastChar==x)return;
	
	int ll=lastChar-'a';
	int xx=x-'a';
	trieNode *_old = prev->nxt[ll];
	prev->nxt[ll]=NULL;
	_old->push_lazy();
	if(prev->nxt[xx]==NULL)prev->nxt[xx] = _old;
	else{
		prev->nxt[xx]->push_lazy();
		prev->nxt[xx]->lazy = _old;
	}
	
}


void solve(int casenum){
	int n,qt,m;
	root = new trieNode();
	cin>>n;
	string s;
	while(n--){
		cin>>s;
		insert(s);
	}
	char c;
	cin>>m;
	while(m--){
		cin>>qt>>s;
		if(qt==1){
			cin>>c;
			update(s,c);
		}
		else if(qt==2)cout<<query(s)<<"\n";
	}
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}