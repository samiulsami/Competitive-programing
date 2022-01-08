const int _chars=26;
int BIT[N]={0};
vi graph[N];
int Time=0;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,lvl=0;
        bool terminal=0;
        int next_terminal=-1;
        int st,ed;
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
        return id;
    }

    void dfs(int u){
        trie[u].st=++Time;
        for(int v:graph[u])dfs(v);
        trie[u].ed=Time;
    }

    void update(int ind){
        ind=trie[id].st;
        while(ind<=Time){
            BIT[ind]++;
            ind+=(ind&-ind);
        }
    }

    int query(int ind){
        int ret=0;
        while(ind>0){
            ret+=BIT[ind];
            ind-=(ind&-ind);
        }
        return ret;
    }

    int get(int id){
        return query(trie[id].ed) - query(trie[id].st-1);
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
        dfs(0);
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }
};
