#include<bits/stdc++.h>
using namespace std;

const int _chars=26;

vector<int>graph[1000005];
int BIT[1000006]={0};
int Time=0;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int st,ed,link=0,lvl=0;
        trienode(int lvl):lvl(lvl){}
    };

    vector<trienode>trie;
    AhoCorasick(){
        trie.emplace_back(0);
    }

    int insert(const char *s){
        int id=0;
        for(int i=0; s[i]; i++){
            int c = s[i]-'a';
            if(!trie[id].next[c]){
                trie.emplace_back(trie[id].lvl+1);
                trie[id].next[c]=(int)trie.size()-1;
            }
            id = trie[id].next[c];
        }
        return id;
    }

    void modify(int id, int val){
        update(trie[id].st, val);
        update(trie[id].ed+1, -val);
    }

    void update(int ind, int val){
        while(ind<=Time){
           BIT[ind]+=val;
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

    void dfs(int u){
        trie[u].st=++Time;
        for(int v:graph[u])
            dfs(v);
        trie[u].ed=Time;
    }

    void build(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int id = q.front();
            q.pop();
            //trie[id].next_terminal = (trie[trie[id].link].terminal) ? trie[id].link : trie[trie[id].link].next_terminal;
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c]){
                    trie[trie[id].next[c]].link = id ? trie[trie[id].link].next[c] : 0;
                    q.push(trie[id].next[c]);
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }

        for(int i=1; i<(int)trie.size(); i++){
            graph[trie[i].link].push_back(i);
        }
        dfs(0);
    }

    inline int getnext(int id, char c){
        return trie[id].next[c-'a'];
    }

    int get(const char *s){
        int ret=0;
        int x=0;
        for(int i=0; s[i]; i++){
            x=getnext(x,s[i]);
            ret+=query(trie[x].st);
        }
        return ret;
    }
};

const int N = 1e5+5;

int a[N];
char s[1000005];
bool status[100005]={0};

int main(){
    int n,k;
    scanf("%d%d",&n,&k);

    AhoCorasick ac;
    for(int i=1; i<=k; i++){
        scanf(" %s",&s);
        a[i] = ac.insert(s);
    }
    ac.build();

    for(int i=1; i<=k; i++){
            ac.modify(a[i],1);
            status[i]=1;
    }

    char c;
    int id;

    while(n--){
        scanf(" %c",&c);
        if(c=='+'){
            scanf("%d",&id);
            if(!status[id])ac.modify(a[id],1);
            status[id]=1;
        }
        else if(c=='-'){
            scanf("%d",&id);
            if(status[id])ac.modify(a[id],-1);
            status[id]=0;
        }
        else{
            scanf("%s",&s);
            printf("%d\n",ac.get(s));
        }
    }
return 0;
}
