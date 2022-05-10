#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;

#define sf scanf
#define pf printf
#define nl printf("\n");
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
#define si(x) scanf("%d",&x);
#define sii(x,y) scanf("%d%d",&x,&y);
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z);
#define sl(x) scanf("%lld",&x);
#define sll(x,y) scanf("%lld%lld",&x,&y);
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define FOR(i,j,n) for(int i=j; i<=n; i++)
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;

typedef array<ll,3> pii;

struct node{
    ll a,b,c;
    node *left,*right;
    node(){a=b=c=0;left=right=this;}
    node(ll a, ll b, ll c, node *left=NULL, node *right=NULL):a(a),b(b),c(c),left(left),right(right){}
}Tree[21*N];
int nodeCnt=0;

int arr[N];
int a[N],b[N];

inline node *newNode(ll a=0, ll b=0, ll c=0, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(a,b,c,left,right);
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

node *update(node *cur, int l, int r, int pos, ll a, ll b){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(a,b,1);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,a,b);
    tmp->right = update(cur->right,mid+1,r,pos,a,b);
    tmp->a = tmp->left->a + tmp->right->a;
	tmp->b = tmp->left->b + tmp->right->b;
	tmp->c = tmp->left->c + tmp->right->c;
    return tmp;
}

int Find(node *R, node *L, int l, int r, ll aSum, ll bSum){
	if(l==r){
		if(aSum<=bSum)return R->c - L->c;
		return 0;
	}
	
	ll x = aSum + R->left->a - L->left->a;
	ll y = bSum + R->right->b - L->right->b;
	
	int mid = (l+r)>>1;
	
	if(x>y)return Find(R->left, L->left, l, mid, aSum, y);
	return R->left->c - L->left->c + Find(R->right, L->right, mid+1, r, x, bSum);
}


void solve(int casenum){
	int n,q;
	sii(n,q);
	vector<pii>tmp;
	for(int i=0; i<n; i++){
		si(arr[i]);
		tmp.push_back({arr[i],i});
	}
	
	sort(all(tmp));
	
	for(int i=0; i<n; i++){
		si(a[i]);
		arr[tmp[i][1]]=tmp[i][0];
	}
	
	vector<node*>roots;
	roots.push_back(newNode());
	build(roots.back(),1,n+5);
	
	for(int i=0; i<n; i++){
		si(b[i]);
		roots.push_back(update(roots.back(), 1, n, arr[i], a[i],b[i]));
	}
	
	int l,r,ans;
	while(q--){
		sii(l,r);
		ans = Find(roots[r], roots[l-1], 1, n, 0, 0);
		pf("%d %d\n",ans, r-l+1-ans);
	}
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
	//scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}