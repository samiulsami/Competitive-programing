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


const int N = 2e5+5;


struct node{
    int lazy,mx,mn;
    node *left, *right;
    node(){
        lazy=0;
        left=NULL;
        right=NULL;
    }
    node(ll lazy, node *left=NULL, node *right=NULL):lazy(lazy),left(left),right(right){
		mx=0;
		mn=0;
	}
};
int nodeCnt=0;

inline node *newNode(int mn, int mx, node *left=NULL, node *right=NULL){
    node *ret = new node(0,left, right);
	ret->mn=mn;
	ret->mx=mx;
    return ret;
}

inline void expand(node *cur, int l, int r){
	if(l==r)return;
	int mid = (l+r)>>1;
    if(cur->left==NULL)cur->left = newNode(l,mid);
    if(cur->right==NULL)cur->right = newNode(mid+1,r);
}

inline void push_update(node *cur, int l, int r){
    if(cur->lazy!=0){
		cur->mx += cur->lazy;
		cur->mn += cur->lazy;
        if(l!=r){
            expand(cur,l,r);
            cur->left->lazy += cur->lazy;
            cur->right->lazy += cur->lazy;
        }
        cur->lazy=0;
    }
}

void update(node *cur, int l, int r, int posl, int posr, int t){
    push_update(cur,l,r);
    if(l>r || (cur->mx==cur->mn && cur->mx==t))return;
    if(cur->mx<t){
        cur->lazy++;
        push_update(cur,l,r);
    }
	else if(cur->mn>t){
		cur->lazy--;
        push_update(cur,l,r);
	}
    else{
        int mid = (l+r)>>1;
        expand(cur,l,r);
        update(cur->left, l, mid, posl, posr, t);
        update(cur->right, mid+1, r, posl, posr, t);
		cur->mn = min(cur->left->mn, cur->right->mn);
		cur->mx = max(cur->left->mx, cur->right->mx);
    }
}

ll query(node *cur, int l, int r, int pos){
    push_update(cur,l,r);
    if(l>r || l>pos|| r<pos)return 0;
    if(l==pos && r==pos)return cur->mx;
    int mid = (l+r)>>1;
    expand(cur,l,r);
    if(pos<=mid)return query(cur->left, l, mid, pos);
	return query(cur->right, mid+1, r, pos);
}

void solve(int casenum){
	int lim = 1e9+1;
	node *root = newNode(0,1e9);
	int n,x,t,k,lastans=0;
	si(n);
	for(int i=0,l,r; i<n; i++){
		sii(t,k);
		// if(t>0)update(root,0,1e9,0,t-1,1);
		// if(t<1e9)update(root,0,1e9, t+1, 1e9,-1);
		update(root,0,1e9,0,1e9,t);
		while(k--){
			si(x);
			x = (x+lastans)%lim;
			lastans = query(root,0,1e9,x);
			pf("%d\n",lastans);
		}
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