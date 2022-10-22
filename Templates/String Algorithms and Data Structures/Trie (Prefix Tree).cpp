const int _chars = 26;
struct trieNode{
    int cnt;
    int endmark;
    trieNode *nxt[_chars];
    trieNode(){
        endmark=0;
        cnt=0;
        for(int i=0; i<_chars; i++)nxt[i]=NULL;
    }
}*root;

void trie_insert(string &s){
    if(root==NULL)root = new trieNode;
    trieNode *cur=root;

    for(int i=0,chr,len=s.length(); i<len; i++){
        chr = s[i]-'a';
        if(cur->nxt[chr]==NULL){
            cur->nxt[chr] = new trieNode;
        }
        cur=cur->nxt[chr];
        cur->cnt++;
    }
    cur->endmark++;
}

int trie_search(string &s){
    trieNode *cur=root;

    for(int i=0,chr,len=s.length(); i<len; i++){
        chr=s[i]-'a';
        if(cur->nxt[chr])cur=cur->nxt[chr];
        else return 0;
    }

    return cur->endmark;
}

bool trie_erase(string &s, trieNode *cur=root, int i=0){
    if(i==(int)s.length())return (bool)cur->endmark;

    int chr=s[i]-'a';
    if(cur->nxt[chr] && trie_erase(s,cur->nxt[chr],i+1)){
        trieNode *nxtNode = cur->nxt[chr];
        nxtNode->cnt--;
        if(i==s.length()-1)nxtNode->endmark--;
        if(nxtNode->cnt==0){
            free(nxtNode);
            cur->nxt[chr]=NULL;
        }

        return 1;
    }
    return 0;
}

string display;

void display_trie(trieNode *cur){
    if(cur==NULL)return;

    for(int j=0; j<cur->endmark; j++){
        cout<<display<<endl;
    }

    for(int i=0; i<_chars; i++){
        if(cur->nxt[i]){
                display.push_back(char(i+'a'));
                display_trie(cur->nxt[i]);
                display.pop_back();
        }
    }
}

void delete_trie(trieNode *cur){
    if(cur==NULL)return;
    for(int i=0; i<_chars; i++)
        if(cur->nxt[i])delete_trie(cur->nxt[i]);
    free(cur);
}

