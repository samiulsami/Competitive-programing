#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}
template<typename T>inline void togglebit(T &x, int pos){x^=(T(1)<<pos);}
template<typename T>inline bool chkbit(T x, int pos){return bool(x&(T(1)<<pos));}
template<typename T>inline void setbit(T &x, int pos){x|=(T(1)<<pos);}
template<typename T>inline void resetbit(T &x, int pos){if(chkbit(x,pos))togglebit(x,pos);}


const int N = 1e5+5;

struct node{
    int data;
    node *left, *right;
    node(){
        data=0;
        left=NULL;
        right=NULL;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[24*N];
int nodeCnt=0;

inline node *newNode(int data,  node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data, left, right);
    return &Tree[nodeCnt++];
}

inline void expand(node *cur, int l, int r, int mid){
    if(cur->left==NULL)cur->left = newNode(mid-l+1,0);
    if(cur->right==NULL)cur->right = newNode(r-mid,0);
}

void update(node *cur, int l, int r, int pos){
	int mid = (l+r)>>1;
	expand(cur,l,r,mid);
    if(l==pos && r==pos)cur->data=0;
    else{
        if(pos<=mid)update(cur->left, l, mid, pos);
        else update(cur->right, mid+1, r, pos);
        cur->data = cur->left->data + cur->right->data;
    }
}

int kth(node *cur, int l, int r, int k){
	if(l==r)return l;
	int mid = (l+r)>>1;
	expand(cur,l,r,mid);
	if(cur->left->data >= k)return kth(cur->left, l, mid, k);
	return kth(cur->right, mid+1, r, k - cur->left->data);
}

void solve(int casenum){
	int n,m,x;
	char c;
	sii(n,m);
	node *root = newNode(n,0);
	
	while(m--){
		sf(" %c%d",&c,&x);
		x = kth(root,1,n,x);
		if(c=='D')update(root,1,n,x);
		else pf("%d\n",x);
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    //scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}