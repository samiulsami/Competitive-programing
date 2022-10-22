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


const int N = 5005;


const int _chars=26;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1,lvl=0;
        bool terminal=0;
		trienode(){}
        trienode(int lvl):lvl(lvl){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back(0);}

    void insert(const string &s){
        int id=0;
        for(int i=0; i<s.length(); i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
                trie.emplace_back(trie[id].lvl+1);
                trie[id].next[c]=(int)trie.size()-1;
            }
            id = trie[id].next[c];
        }
        trie[id].terminal=1;
    }

    void build(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int id = q.front();
            q.pop();
            trie[id].next_terminal = (trie[trie[id].link].terminal) ? trie[id].link : trie[trie[id].link].next_terminal;
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c]){
                    trie[trie[id].next[c]].link = id ? trie[trie[id].link].next[c] : 0;
                    q.push(trie[id].next[c]);
                    ///propagate count of strings through suffix links
                    ///trie[trie[id].next[c]].cnt+=trie[trie[trie[id].next[c]].link].cnt;
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }
}ac;

vi graph[N];
int dp[N];
int n;
const int MOD = 1e9+7;

int f(int i){
	if(i==n)return 1;
	int &ret = dp[i];
	if(~ret)return ret;
	ret=0;
	for(int v:graph[i])ret=(ret+f(v))%MOD;
	return ret;
}

void solve(int casenum){
	int k;
	string s,x;
	cin>>s>>k;
	n=sz(s);
	for(int i=0; i<k; i++){
		cin>>x;
		ac.insert(x);
	}
	ac.build();
	
	int cur=0;
	for(int i=0,nextT; i<sz(s); i++){
		cur=ac.getnext(cur,s[i]);
		if(ac.trie[cur].terminal)nextT=cur;
		else nextT=ac.trie[cur].next_terminal;
		
		while(nextT!=-1){
			graph[i-ac.trie[nextT].lvl+1].push_back(i+1);
			nextT=ac.trie[nextT].next_terminal;
		}
	}
	

	cout<<f(0)<<endl;
}

int main(){
	memset(dp,-1,sizeof(dp));
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
   // freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}