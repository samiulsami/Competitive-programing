#include<bits/stdc++.h>
/*
    Problem: Codeforces Round #260 (Div. 1) -  B. A Lot of Games
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

const int _chars = 26;
struct trieNode{
    bool winning;
    trieNode *nxt[_chars];
    trieNode(){
        winning=0;
        for(int i=0; i<_chars; i++)nxt[i]=NULL;
    }
}*root=NULL,*root1=NULL;

void trie_insert(string &s, trieNode *cur){

    for(int i=0,chr,len=s.length(); i<len; i++){
        chr = s[i]-'a';
        if(cur->nxt[chr]==NULL){
            cur->nxt[chr] = new trieNode;
        }
        cur=cur->nxt[chr];
    }
}

bool make_tree(trieNode *cur){
    cur->winning=1;

    bool lastChar=1;
    for(int i=0; i<_chars; i++){
        if(cur->nxt[i]){
            if(make_tree(cur->nxt[i]))
                cur->winning=0;
            lastChar=0;
        }
    }
    if(lastChar)cur->winning=1;
    return cur->winning;
}

bool make_tree1(trieNode *cur){
    cur->winning=1;

    bool lastChar=1;
    for(int i=0; i<_chars; i++){
        if(cur->nxt[i]){
            if(make_tree1(cur->nxt[i]))
                cur->winning=0;
            lastChar=0;
        }
    }
    if(lastChar)cur->winning=0;
    return cur->winning;
}


inline void Solve(int Case){
    int n,k;
    cin>>n>>k;
    string s;
    root = new trieNode;
    root1 = new trieNode;
    FOR(i,n){
        cin>>s;
        trie_insert(s,root);
        trie_insert(s,root1);
    }


    make_tree(root);
    make_tree1(root1);

    bool winning=0,losing=0;
    for(int i=0; i<_chars; i++){
        if(root->nxt[i]){
            if(root->nxt[i]->winning)winning=1;
        }
        if(root1->nxt[i]){
            if(root1->nxt[i]->winning)losing=1;
        }
    }
    //cout<<winning<<" "<<losing<<endl;
    bool first=0;
    if(k&1){
        if(winning)first=1;
    }
    else if(winning && losing)first=1;

    if(first)cout<<"First"<<endl;
    else cout<<"Second"<<endl;
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
