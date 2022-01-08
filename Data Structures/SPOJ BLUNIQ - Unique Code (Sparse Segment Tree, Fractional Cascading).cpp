#include<bits/stdc++.h>

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


///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int N = 1e5+5;

struct node{
    int data;
    node *left, *right;
    node(){
        data=0;
        left=NULL;
        right=NULL;
    }
    node(ll data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[40*N];
int nodeCnt=0;

inline node *newNode(ll data=0,node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data, left, right);
    return &Tree[nodeCnt++];
}

inline void expand(node *cur, int l, int r){
    int mid=(l+r)>>1;
    if(cur->left==NULL)cur->left = newNode(mid);
    if(cur->right==NULL)cur->right = newNode(r);
}

void update(node *cur, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return;
    else if(l==pos && r==pos){
           // pf("%d %d %d\n",l,r,val);
            cur->data=val;
    }
    else{
        int mid = (l+r)>>1;
        expand(cur,l,r);
        if(pos<=mid)update(cur->left, l, mid, pos, val);
        else update(cur->right, mid+1, r, pos, val);
        cur->data = max(cur->left->data, cur->right->data);
    }
}

int Find(node *cur, int l, int r, int k){
    if(l==r)return l;
    int mid = (l+r)>>1;
    expand(cur,l,r);
    int cnt=cur->left->data;
    if(cnt>=k)return Find(cur->left, l, mid, k);
    return Find(cur->right,mid+1,r,k);

}

inline void Solve(int Case){
    int n;
    si(n);

    node *root = newNode();
    int lim = 1e9+n+n;
    expand(root,1,lim);

    int i,x;
    while(n--){
        sii(i,x);
        if(i==1){
            x=Find(root,1,lim,x);
            pf("%d\n",x);
            update(root,1,lim,x,-1e9);
        }
        else{
            update(root,1,lim,x,x);
        }
    }

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
