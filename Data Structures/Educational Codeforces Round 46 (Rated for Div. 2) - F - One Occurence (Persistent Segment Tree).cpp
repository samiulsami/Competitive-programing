#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef long double ld;
typedef array<int,2> pii;
#define sf scanf
#define pf printf
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<"\n"
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<"\n"
mt19937_64 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline ll rand(ll l, ll r){uniform_int_distribution<ll> RNG(l,r);return RNG(rng);}

const int N = 5e5+5;

struct node{
    array<int,2> data;
    node *left,*right;
    node(){
		data = {(int)1e9,(int)1e9};
        left=right=this;
    }
	node(array<int,2> a, node *left, node *right):data(a), left(left), right(right){}
}Tree[42*N];
int nodeCnt=0;

inline node *newNode(int a=1e9, int b=1e9, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node({a,b},left,right);
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
    if(l==pos && r==pos)return newNode(val,pos);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,val);
    tmp->right = update(cur->right,mid+1,r,pos,val);
    tmp->data = min(tmp->left->data, tmp->right->data);
    return tmp;
}

array<int,2> query(node *cur, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    if(posl>mid)return query(cur->right, mid+1, r, posl, posr);
    if(posr<=mid)return query(cur->left, l, mid, posl, posr);
    return min(query(cur->left, l, mid, posl, posr), query(cur->right, mid+1, r, posl, posr));
}

int arr[N];
int last[N];
node *nodes[N];

void solve(int casenum){
	int n;
	sf("%d",&n);
	for(int i=1; i<=n; i++){
		sf("%d",&arr[i]);
		last[arr[i]]=-1;
	}
	
	nodes[0] = newNode();
	build(nodes[0],1,n);
	
	for(int i=1; i<=n; i++){
		node *cur = nodes[i-1];
		if(last[arr[i]]!=-1){
			cur = update(cur, 1, n, last[arr[i]], 1e9);
			
		}
		cur = update(cur, 1, n, i, last[arr[i]]);
		last[arr[i]]=i;
		nodes[i]=cur;
	}
	
	int q;
	sf("%d",&q);
	for(int i=0,l,r; i<q; i++){
		sf("%d%d",&l,&r);
		auto x = query(nodes[r],1,n,l,r);
		if(x[0]>=l)pf("0\n");
		else pf("%d\n",arr[x[1]]);
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