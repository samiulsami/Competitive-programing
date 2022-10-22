#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}
const int N = 2e5+5;

const int _chars=26;
struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1,cnt=0,lvl=0;
        bool terminal=0;
        vector<int>occ;
        vector<pii(2)>queries;
        trienode(int x=0){lvl=x;}
    };

    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back(0);}
    int insert(const string &s, int queryID, int k){
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
        trie[id].queries.push_back({queryID,k});
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
                    ///propagate count of strings through suffix links
                    ///trie[trie[id].next[c]].cnt+=trie[trie[trie[id].next[c]].link].cnt;
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }


    void work(vector<int> &ans){
    	queue<int>q;
        q.push(0);
        map<int,int>vis;
        vis[0]=1;
        while(!q.empty()){
            int id = q.front();
            q.pop();
        	sort(all(trie[id].occ));
        	for(auto it:trie[id].queries){
        		if(it[1]<=sz(trie[id].occ))ans[it[0]] = trie[id].occ[it[1]-1];
        		else ans[it[0]]=-1;
        	}
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c] && !vis.count(trie[id].next[c])){
                    q.push(trie[id].next[c]);
                    vis[trie[id].next[c]]=1;
                }
            }
        }
    }

    inline int getnext(int id, char c){return trie[id].next[c-'a'];}
}ac;


inline void solve(int caseNum){
	string s;
	cin>>s;
	int n = s.length();

	int q,k;
	string t;
	cin>>q;
	for(int i=0; i<q; i++){
		cin>>t>>k;
		ac.insert(t,i,k);
	}

	ac.build();

	int id=0;
	vector<int>ans(q,-1);
	int i=0;
	for(char c:s){
		i++;
		id = ac.getnext(id,c);
		int cur;
		if(ac.trie[id].terminal)cur=id;
		else cur = ac.trie[id].next_terminal;

		while(cur!=-1){
			ac.trie[cur].occ.push_back(i-ac.trie[cur].lvl+1);
			int nxt = ac.trie[cur].next_terminal;
			cur=nxt;
		}
	}

	ac.work(ans);
	for(int i:ans)cout<<i<<"\n";

}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}