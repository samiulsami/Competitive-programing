#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
#define ff first
#define ss second
#define sf scanf
#define pf printf
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define FOR(i,n) for(int i=0; i<n; i++)
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc()};
mt19937 rng(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}
///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------

const int N = 5e5+5;
const int _hashCnt=2;
const int mod1 = (1LL<<31)-1;
const int bases[_hashCnt] = {rand(11887,1<<21),rand(15661,1<<22)};

int P[_hashCnt][15];
int H[2][13];
inline int mod(ll x) {
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n){
        for(int ind=0; ind<_hashCnt; ind++){
            H[ind][0]=0;
            for(int i=0;i<n; i++){
                H[ind][i+1] = mod((1LL*H[ind][i]*bases[ind]) + ((ll)s[i]));
            }
        }
    }
    inline ll combineHash(int h1, int h2){return (ll(h1)<<32)^ll(h2);}
    inline int singleHash(int l, int r, int ind=0){
        int h = H[ind][r] - mod(1LL*H[ind][l-1] * P[ind][r-l+1]);
        return (h<0?h+mod1:h);
    }
    inline ll getHash(int l, int r){return combineHash(singleHash(l,r,0), singleHash(l,r,1));}
};

char s[15];
struct node{
    short data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
};

int nodeCnt=0;
node Tree[100*N];

inline node *newNode(int data=0, node *left=NULL, node *right=NULL){
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r){
        return;
    }
    cur->left = newNode();
    cur->right = newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
    cur->data = cur->left->data + cur->right->data;
}

node *cloneAndUpdate(node *cur, int l, int r, int pos, int val){
    if(l>pos || r<pos)return cur;
    if(l==r){
        node *tmp = newNode(cur->data+val);
        return tmp;
    }
    node *tmp = newNode();
    int mid = (l+r)>>1;
    tmp->left = cloneAndUpdate(cur->left,l,mid,pos,val);
    tmp->right = cloneAndUpdate(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left,l,mid,posl,posr) + query(cur->right,mid+1,r,posl,posr);
}

inline void Solve(int Case){
    int n,len;
    vector<node*>roots;
    map<ll,int>mp;
    int hashCnt=0;
    roots.emplace_back(newNode());
    build(roots.back(),1,N);

    si(n);
    FOR(i,n){
        sf(" %s",&s);
        len=strlen(s);
        Hash a(s,len);
        set<ll>hashes;

        for(int i=1; i<=len; i++){
            for(int j=1; j+i-1<=len; j++){
                hashes.insert(a.getHash(j,j+i-1));
            }
        }

        node *tmp=roots.back();
        for(ll x:hashes){
            if(mp.count(x))x=mp[x];
            else {
                mp[x]=hashCnt;
                x=hashCnt;
                hashCnt++;
            }
            tmp=cloneAndUpdate(tmp,1,N,x,1);
        }
        roots.push_back(tmp);
    }

    int q,l,r;
    ll tmpHash;
    si(q);
    while(q--){
        sii(l,r);
        sf(" %s",&s);
        len=strlen(s);
        Hash a(s,strlen(s));
        tmpHash = a.getHash(1,len);
        if(!mp.count(tmpHash)){
            pf("0\n");
        }
        else{
            tmpHash=mp[tmpHash];
            pf("%d\n",query(roots[r],1,N,tmpHash,tmpHash)-query(roots[l-1],1,N,tmpHash,tmpHash));
        }
    }
}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //#define Multiple_Test_Cases
  //#define fastio
int main(){
    for(int i=0; i<_hashCnt; i++){
        P[i][0]=1;
        for(int j=1; j<=12; j++)P[i][j]=mod(1LL*P[i][j-1]*bases[i]);
    }
    #ifdef fastio
        ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #endif
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        #ifdef fastio
            cin>>T;
        #else
            scanf("%d",&T);
        #endif
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
