#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
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
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;


const int _chars=26;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1,cnt=0,lvl=0;
        bool terminal=0;
        trienode(int lvl):lvl(lvl){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back(0);}

    int insert(const string &s){
        int id=0;
        for(int i=0; i<s.length(); i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
                trie.emplace_back(trie[id].lvl+1);
                trie[id].next[c]=(int)trie.size()-1;
            }
            id = trie[id].next[c];
        }
        trie[id].cnt++;
        trie[id].terminal=1;
        return id;
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
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }
}ac;

ll start[N]={0};
ll finish[N]={0};

void solve(int casenum){
	string t,s;
	cin>>t;
	int n;
	cin>>n;
	
	for(int i=0; i<n; i++){
		cin>>s;
		ac.insert(s);
	}
	
	ac.build();
	int id=0,cur;
	for(int i=0; i<sz(t); i++){
		id=ac.getnext(id,t[i]);
		if(ac.trie[id].terminal)cur=id;
		else cur=ac.trie[id].next_terminal;
		
		while(cur!=-1){
			finish[i]+=ac.trie[cur].cnt;
			start[i-ac.trie[cur].lvl+1]+=ac.trie[cur].cnt;
			cur = ac.trie[cur].next_terminal;
		}
	}

	ll ans=0;
	for(int i=0; i<sz(t)-1; i++){
		ans+=finish[i]*start[i+1];
	}
	
	cout<<ans<<endl;


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