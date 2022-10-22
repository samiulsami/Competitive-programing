#include<iostream>
/*
    Problem: http://acm.hdu.edu.cn/showproblem.php?pid=2846
    Verdict: AC
*/
using namespace std;

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const int _chars = 26;
struct trieNode{
    short cnt,curInd;
    trieNode *nxt[_chars];
    trieNode(){
        cnt=0;
        curInd=-1;
        for(short i=0; i<_chars; i++)nxt[i]=NULL;
    }
}*root=NULL;

void trie_insert(char *s, int i, short color){
    if(root==NULL)root = new trieNode;
    trieNode *cur=root;

    for(int chr; s[i]; i++){
        chr = s[i]-'a';
        if(cur->nxt[chr]==NULL){
            cur->nxt[chr] = new trieNode;
        }
        cur=cur->nxt[chr];
        if(cur->curInd!=color)cur->cnt++;
        cur->curInd=color;
    }
}

int trie_search(char *s){
    trieNode *cur=root;

    for(int i=0,chr; s[i]; i++){
        chr=s[i]-'a';
        if(cur->nxt[chr])cur=cur->nxt[chr];
        else return 0;
    }

    return cur->cnt;
}


inline void Solve(int Case){
    int p,q;
    char s[21];
    scanf("%d",&p);

    while(p--){
        scanf(" %s",&s);
        for(int i=0; s[i]; i++)
            trie_insert(s,i,p);
    }

    scanf("%d",&q);
    while(q--){
        scanf(" %s",&s);
        printf("%d\n",trie_search(s));
    }
    //display_trie(root);

}

  //#define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
