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

const int N = 1e5+5;


const int _chars=26;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1;
        bool terminal=0;
		int i=0,lvl=0;
        trienode(int lvl):lvl(lvl){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back(0);}

    void insert(const string &s, int i){
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
		trie[id].i=i;
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

string fix(string s){
	for(char &c:s)if(c>='A' && c<='Z')c+=32;
	reverse(all(s));
	return s;
}

vector<pii>graph[N];
int dp[N],len;
pii dir[N];
string strings[N];

int f(int i){
	if(i>len)return 0;
	if(i==len)return 1;
	int &ret = dp[i];
	if(~ret)return ret;
	ret=0;

	for(pii &e:graph[i]){
		int nxt=(int)strings[e.second].size();
		if(f(e.first+1)){
			ret=1;
			dir[i]=e;
			return ret;
		}
	}
	return ret;
}

void solve(int casenum){
	memset(dp,-1,sizeof(dp));
	int n;
	cin>>len;
	string s;
	cin>>s;
	cin>>n;

	FOR(i,n){
		cin>>strings[i];
		string tmp = fix(strings[i]);
		ac.insert(tmp,i);
	}
	ac.build();
	
	int id=0,cur=-1;
	for(int i=0; i<sz(s); i++){
		id=ac.getnext(id,s[i]);
		
		if(ac.trie[id].terminal)cur=id;
		else cur = ac.trie[id].next_terminal;
		
		while(cur!=-1){
			graph[i-ac.trie[cur].lvl+1].push_back(pii(i,ac.trie[cur].i));
			cur=ac.trie[cur].next_terminal;
		}
	}
	
	
	f(0);
	int i=0;
	while(i<len){
		cout<<strings[dir[i].second]<<" ";
		i=dir[i].first+1;
	}
	cout<<endl;

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