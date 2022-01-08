#include<bits/stdc++.h>

using namespace std;
typedef int64_t ll;
typedef uint64_t ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define ff first
#define ss second
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

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int N = 1e5+5;

struct node{
    int data;
    node *left,*right;
    node(){
        left=right=this;
        data=0;
    }
}Tree[2*N];
int nodeCnt=0;

inline node *newNode(int data=0){
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r)cur->data=0;
    else{
        int mid = (l+r)>>1;
        cur->left = newNode();
        cur->right = newNode();
        build(cur->left,l,mid);
        build(cur->right,mid+1,r);
    }
}

void update(node *cur, int l, int r, int pos, int val){
    if(pos>r || pos<l || l>r)return;
    if(l==pos && r==pos)cur->data=val;
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(cur->left, l, mid, pos, val);
        else update(cur->right, mid+1, r, pos, val);
        cur->data = cur->left->data + cur->right->data;
    }
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left, l, mid, posl, posr) + query(cur->right, mid+1, r, posl, posr);
}

int prevPos[N];
int mpCnt=0;
int arr[N];

struct queryData{
    int l,r,ind;
    queryData(){}
    queryData(int l, int r, int ind):l(l),r(r),ind(ind){}
    bool operator<(const queryData &q)const{
        return r<q.r;
    }
}queries[N];
int ans[N];

inline void Solve(int Case){
    nodeCnt=0;
    int n,q,l,r;
    sii(n,q);

    node *root = newNode();
    build(root,1,n);
    memset(prevPos,-1,sizeof(prevPos));

    for(int i=1; i<=n; i++)si(arr[i]);

    for(int i=1; i<=q; i++){
        sii(l,r);
        queries[i]=queryData(l,r,i);
    }
    sort(queries+1,queries+q+1);
    int maxR=1;

    for(int i=1; i<=q; i++){
        queryData &Q = queries[i];
        //pf("%d %d\n",Q.l,Q.r);
        for(int i=maxR; i<=Q.r; i++){
            if(prevPos[arr[i]]!=-1){
                update(root,1,n,prevPos[arr[i]],0);
            }
            update(root,1,n,i,1);
            prevPos[arr[i]]=i;
        }
        maxR=Q.r;
        ans[Q.ind]=query(root,1,n,Q.l,Q.r);
    }

    pf("Case %d:\n",Case);
    for(int i=1; i<=q; i++)pf("%d\n",ans[i]);

}



///-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #define Multiple_Test_Cases
  //#define fastio
int main(){
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
