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
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[21*N];
int nodeCnt=0;

inline node *newNode(int data=1e9, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data,left,right);
    return &Tree[nodeCnt++];
}

void build(node *cur, int l, int r){
    if(l==r)return;
    cur->left=newNode();
    cur->right=newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
}

node *update(node *cur, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(val);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,val);
    tmp->right = update(cur->right,mid+1,r,pos,val);
    tmp->data = min(tmp->left->data,tmp->right->data);
    return tmp;
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    if(posl>mid)return query(cur->right, mid+1, r, posl, posr);
    if(posr<=mid)return query(cur->left, l, mid, posl, posr);
    return min(query(cur->left, l, mid, posl, posr),query(cur->right, mid+1, r, posl, posr));
}

int n;
int lvl[N];
vi graph[N];
int dTime[N];
int eTime[N];
int Time=0;
int a[N];
node *root[N];
vi tmp[N];

void dfs(int u, int p){
	dTime[u]=++Time;
	tmp[lvl[u]].push_back(u);
	for(int v:graph[u]){
		if(v^p){
			lvl[v]=lvl[u]+1;
			dfs(v,u);
		}
	}
	eTime[u]=Time;
}

void solve(int casenum){
	int r,m;
	sii(n,r);
	for(int i=1; i<=n; i++)si(a[i]);
	for(int i=1,u,v; i<n; i++){
		sii(u,v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	lvl[r]=1;
	root[0]=newNode();
	build(root[0],1,n);
	dfs(r,-1);
	for(int i=1; i<=n; i++){
		root[i]=root[i-1];
		for(int &v:tmp[i]){
			root[i]=update(root[i],1,n,dTime[v],a[v]);
		}
	}
	
	int x,y,last=0;
	si(m);
	while(m--){
		sii(x,y);
		x=((x+last)%n) + 1;
		y=(y+last)%n;
		last = query(root[min(n,lvl[x]+y)],1,n,dTime[x],eTime[x]);
		pf("%d\n",last);
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