const int _chars=26;
struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0,next_terminal=-1,cnt=0;
        bool terminal=0;
        trienode(){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back();}
    int insert(const string &s){
        int id=0;
        for(int i=0; i<s.length(); i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
                trie.emplace_back();
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
                    ///propagate count of strings through suffix links
                    ///trie[trie[id].next[c]].cnt+=trie[trie[trie[id].next[c]].link].cnt;
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }
    inline int getnext(int id, char c){return trie[id].next[c-'a'];}
};
