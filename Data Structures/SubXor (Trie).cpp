#include<bits/stdc++.h>
/*
    Problem: SPOJ SUBXOR - SubXor
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

int arr[MAX];
int n,k;

const int _chars = 2;
struct trieNode{
    int cnt;
    trieNode *nxt[_chars];
    trieNode(){
        cnt=0;
        for(int i=0; i<_chars; i++)nxt[i]=NULL;
    }
}*root;

void trie_insert(int val,int x=1){
    if(root==NULL)root = new trieNode;
    trieNode *cur=root;

    for(int i=30; i>=0; i--){
        bool chr = bool(val&(1<<i));
        if(cur->nxt[chr]==NULL){
            cur->nxt[chr] = new trieNode;
        }
        cur=cur->nxt[chr];
        cur->cnt+=x;
    }

}

int trie_search(int val){
    trieNode *cur = root;

    int curVal=0;
    int ret=0;
    for(int i=30; i>=0; i--){

        bool bit = bool(val&(1<<i));
        bool nxtbit=bit;
        if(cur->nxt[!bit]){
            if(curVal+(1<<i)>=k){
                    ret+=cur->nxt[!bit]->cnt;
                    nxtbit=bit;
            }
            else{
                curVal+=(1<<i);
                nxtbit=!bit;
            }
        }
        else nxtbit=bit;

        cur=cur->nxt[nxtbit];
        if(cur==NULL)break;

    }
    return ret;
}

void delete_trie(trieNode *cur){
    if(cur==NULL)return;
    for(int i=0; i<_chars; i++)
        if(cur->nxt[i])delete_trie(cur->nxt[i]);
    free(cur);
}

inline void Solve(int Case){
    sii(n,k);
    root = new trieNode;

    ll ans=0;
    trie_insert(0);
    int xorsum=0;
    FOR(i,n){
        si(arr[i]);
        xorsum^=arr[i];
        ans+=trie_search(xorsum);
        trie_insert(xorsum);
    }

    ll cur=n;
    ll tmp = (cur*cur)+cur;
    tmp/=2LL;
    ans = tmp-ans;
    pf("%lld\n",ans);
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
