#include<bits/stdc++.h>
/*
    Problem: LightOJ 1269 - Consecutive Sum
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
template<typename T>inline void setmax(T &a, T &b){b>a?a=b:0;}
template<typename T>inline void setmin(T &a, T &b){b<a?a=b:0;}

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 5e4+5;

const int _chars = 2;
struct trieNode{
    trieNode *nxt[_chars];
    trieNode(){
        for(int i=0; i<_chars; i++)nxt[i]=NULL;
    }
}*root;

void trie_insert(int val){
    if(root==NULL)root = new trieNode;
    trieNode *cur=root;

    for(int i=30; i>=0; i--){
        int bit = bool(val&(1<<i));
        if(cur->nxt[bit]==NULL){
            cur->nxt[bit] = new trieNode;
        }
        cur=cur->nxt[bit];
    }
}

pii trie_search(int val){
    trieNode *cur=root;
    int maxx=0;

    for(int i=30; i>=0; i--){
        bool bit=(val&(1<<i));
        if(cur->nxt[!bit]){
            cur=cur->nxt[!bit];
            maxx|=(1<<i);
        }
        else cur=cur->nxt[bit];
    }

    int minn=0;
    cur=root;

    for(int i=30; i>=0; i--){
        bool bit=(val&(1<<i));
        if(cur->nxt[bit])cur=cur->nxt[bit];
        else {
            minn|=(1<<i);
            cur=cur->nxt[!bit];
        }
    }

    return {maxx,minn};

}

void delete_trie(trieNode *cur){
    if(cur==NULL)return;
    for(int i=0; i<_chars; i++)
        if(cur->nxt[i])delete_trie(cur->nxt[i]);
    free(cur);
}

int arr[MAX];

inline void Solve(int Case){
    int n;
    si(n);
    FOR(i,n)si(arr[i]);

    int xorsum=0;
    trie_insert(0);
    pii ans(-INT_MAX,INT_MAX);

    for(int i=0; i<n; i++){
        xorsum^=arr[i];
        pii tmp = trie_search(xorsum);
        setmax(ans.FF,tmp.FF);
        setmin(ans.SS,tmp.SS);
        trie_insert(xorsum);
    }

    pf("Case %d: %d %d\n",Case,ans.FF,ans.SS);

    delete_trie(root);
    root=NULL;
}

  #define Multiple_Test_Cases
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
