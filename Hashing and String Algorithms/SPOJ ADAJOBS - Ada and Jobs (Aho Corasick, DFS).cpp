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
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e6+5;

const int _chars=26;


struct AhoCorasick{
	struct trienode{
			int next[_chars]={0};
			int link=0,Time=1e9;
			trienode(){}
	};
	vector<trienode>trie;
    AhoCorasick(){trie.emplace_back();}
	vector<vector<int> >graph;

    void insert(const char *s, int i){
        int id=0;
        for(int i=0; s[i]; i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
				trie.emplace_back();
				trie[id].next[c]=(int)trie.size()-1;      
			}
            id = trie[id].next[c];
        }
		trie[id].Time=min(trie[id].Time,i);
    }
	
	void dfs(int u, int val){
		int &ret=trie[u].Time;
		ret=min(ret,val);
		for(int v:graph[u])
			dfs(v,ret);
	}

    void build(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int id = q.front();
            q.pop();
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c]){
                    trie[trie[id].next[c]].link = id ? trie[trie[id].link].next[c] : 0;
                    q.push(trie[id].next[c]);
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
		graph.resize(sz(trie), vector<int>());
		for(int i=1; i<sz(trie); i++)graph[trie[i].link].push_back(i);
		dfs(0,1e9);
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }
}ac;

char s[1000005];

void solve(int casenum){
	int q,qt;
	si(q);
	vector<pair<int,string> >queries;
	for(int i=0; i<q; i++){
		sf("%d %s",&qt,&s);
		if(qt==0)ac.insert(s,i);
		else queries.push_back({i,string(s)});
	}
	ac.build();
	
	for(int i=0; i<sz(queries); i++){
		int id=0;
		bool b=0;
		for(char &c:queries[i].second){
			id=ac.getnext(id,c);
			if(ac.trie[id].Time<queries[i].first){
				b=1;
				break;
			}
		}
			
		if(b)pf("YES\n");
		else pf("NO\n");
		
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