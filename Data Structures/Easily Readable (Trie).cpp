#include<bits/stdc++.h>
/*
    Problem: LightOJ 1114 - Easily Readable
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

const int _chars = 58;
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

void trie_insert(char *s){
    if(root==NULL)root = new trieNode;
    trieNode *cur=root;

    for(int i=0,chr; s[i]; i++){
        chr = s[i]-65;
        if(cur->nxt[chr]==NULL){
            cur->nxt[chr] = new trieNode;
        }
        cur=cur->nxt[chr];
        cur->cnt++;
    }
    cur->endmark++;
}

int trie_search(char *s){
    trieNode *cur=root;

    for(int i=0,chr; s[i]; i++){
        chr=s[i]-65;
        if(cur->nxt[chr])cur=cur->nxt[chr];
        else return 0;
    }

    return cur->endmark;
}

void delete_trie(trieNode *cur){
    if(cur==NULL)return;
    for(int i=0; i<_chars; i++)
        if(cur->nxt[i])delete_trie(cur->nxt[i]);
    free(cur);
}

char s[100005];
char tmp[105];
inline void Solve(int Case){
    root = new trieNode;
    int n,m;
    si(n);
    int len;
    FOR(i,n){
        sf(" %s",&s);
        len=strlen(s);
        if(len>3)sort(s+1,s+len-1);
        trie_insert(s);
        //pf("string: %s\n",s);
    }

    int ind,ans;


    si(m);
    pf("Case %d:\n",Case);
    while(m--){
        ind=0;
        ans=1;
        sf(" %[^\n]",&s);
        len=strlen(s);
        for(int i=0; i<=len; i++){
            if(i==len || !((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z'))){
                if(ind==0)continue;
                tmp[ind]='\0';
                if(ind>3)sort(tmp+1,tmp+ind-1);
                ans*=trie_search(tmp);
                ind=0;
                //pf("string2: %s\n",tmp);
            }
            else if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z'))tmp[ind++]=s[i];
        }
        pf("%d\n",ans);
    }
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
