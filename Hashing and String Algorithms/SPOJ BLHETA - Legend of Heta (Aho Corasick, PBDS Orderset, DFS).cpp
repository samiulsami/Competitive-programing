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
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N = 1e5+5;

int idrem[N]={0};
char s[100005],t[105];
vector<int>graph[300000];
const int _chars=26;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1,lvl=0;
		pii minval = {1e9,0};
        bool terminal=0;
        trienode(int lvl):lvl(lvl){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back(0);}

    void  insert(const char *s, int i){
        int id=0;
        for(int i=0; s[i]; i++){
            int c = s[i]-'A';
            if(!trie[id].next[c]){
                trie.emplace_back(trie[id].lvl+1);
                trie[id].next[c]=(int)trie.size()-1;
				trie[trie[id].next[c]].minval = pii(1e9,sz(trie)-1);
            }
            id = trie[id].next[c];
        }
        trie[id].terminal=1;
		trie[id].minval = pii(min(trie[id].minval.first,i),id);
    }

	void dfs(int u, pii cur){
		pii prop = min(trie[u].minval,cur);
		trie[u].minval=prop;
		for(int v:graph[u]){
			dfs(v,prop);
		}
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
		for(int i=1; i<sz(trie); i++)graph[trie[i].link].push_back(i);
		dfs(0,pii(1e9+2,0));
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'A'];
    }
	
}ac;

char output[100005];

void solve(int casenum){

	int n,len;
	sf("%s %d",&s,&n);
	len = strlen(s);
	orderSet<int>st;
	
	for(int i=0; i<n; i++){
		sf(" %s",&t);
		ac.insert(t,i);
	}
	for(int i=0; i<len; i++)st.insert(i);
	ac.build();
	
	for(int i=0,total,ind,id=0,cur; i<len; i++){
		id=ac.getnext(id,s[i]);
		idrem[i]=id;
		if(ac.trie[id].terminal)cur=id;
		else cur=ac.trie[id].next_terminal;
		
		if(cur!=-1){
			cur = ac.trie[cur].minval.second;
			total=st.order_of_key(i+1);
			for(int j=0; j<ac.trie[cur].lvl; j++){
				ind = total-ac.trie[cur].lvl;
				st.erase(st.find_by_order(ind));
			}
			total = st.order_of_key(i+1);
			if(total>0)id = idrem[*st.find_by_order(total-1)];
			else id=0;

		}
	}
	
	int cnt=0;
	for(int i:st)output[cnt++]=s[i];
	output[cnt]='\0';
	pf("%s\n",output);
}

/*
KAPKAPPAPAKKAPPAAPPAK
1
KAPPA
*/

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