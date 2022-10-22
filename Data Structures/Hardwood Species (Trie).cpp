#include<bits/stdc++.h>
/*
    Problem: UVA - 10226 - Hardwood Species
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define FF first
#define SS second
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

const int _chars = 128;
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
        chr = s[i];
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
        chr=s[i];
        if(cur->nxt[chr])cur=cur->nxt[chr];
        else return 0;
    }

    return cur->endmark;
}

bool trie_erase(string &s, trieNode *cur=root, int i=0){
    if(i==(int)s.length())return (bool)cur->endmark;

    int chr=s[i];
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
int total;

void display_trie(trieNode *cur){
    if(cur==NULL)return;

    if(cur->endmark){
        cout<<display<<" "<<fixed<<setprecision(4)<<(double(cur->endmark)/double(total))*double(100)<<endl;
    }

    for(int i=0; i<_chars; i++){
        if(cur->nxt[i]){
                display.push_back(char(i));
                display_trie(cur->nxt[i]);
                display.pop_back();
        }
    }
    free(cur);
}

void delete_trie(trieNode *cur){
    if(cur==NULL)return;
    for(int i=0; i<_chars; i++)
        if(cur->nxt[i])delete_trie(cur->nxt[i]);
    free(cur);
}

inline void Solve(int Case){
    string s;
    if(Case!=1)cout<<endl;
    total=0;
    while(getline(cin,s)){
        if(s=="")break;
        trie_insert(s);
        total++;
    }

    display_trie(root);
    //delete_trie(root);
    root=NULL;
}

  #define Multiple_Test_Cases
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        cin>>T;
        cin.ignore();
        cin.ignore();
        //si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
