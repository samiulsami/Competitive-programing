#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 1e5+5;

struct rmq{///0 indexed
	#define T int
	static const int K=__lg(N)+2;
	T Table[K][N];
	
	inline T Combine(T &a, T &b){
		return min(a,b);
	}
	
	inline void set(int pos, T val){Table[0][pos]=val;}

	void init(int n){
		for(int i=1; i<=K; i++)
			for(int j=0; j+(1<<i)-1<n; j++)
				Table[i][j] = Combine(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
	}
	
	T query(int l, int r){
		int lg=__lg(r-l+1);
		return Combine(Table[lg][l], Table[lg][r-(1<<lg)+1]);
	}
	
	#undef T
}rmq;

struct node{
    int data,lazy;
    node *left, *right;
    node(){
        data=lazy=0;
        left=NULL;
        right=NULL;
    }
    node(ll data, ll lazy, node *left=NULL, node *right=NULL):data(data),lazy(lazy),left(left),right(right){}
}Tree[102*N];
int nodeCnt=0;

int n;

inline node *newNode(int data, int lazy, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data, lazy,left, right);
    return &Tree[nodeCnt++];
}

int getVal(int l, int r){///0 indexed
	int len = (r-l+1);
	if(len>=n)return rmq.query(0,n-1);
	l%=n;
	int f = min(n-l,len);
	int ret = rmq.query(l,l+f-1);
	len-=f;
	if(len>0)ret = min(ret, rmq.query(0,len-1));
	return ret;
}

inline void expand(node *cur, int l, int r){
	int mid = (l+r)>>1;
    if(cur->left==NULL)cur->left = newNode(getVal(l,mid),0);
    if(cur->right==NULL)cur->right = newNode(getVal(mid+1,r),0);
}

inline void push_update(node *cur, int l, int r){
    if(cur->lazy!=0){
        cur->data = cur->lazy;
        if(l!=r){
            expand(cur,l,r);
            cur->left->lazy = cur->lazy;
            cur->right->lazy = cur->lazy;
        }
        cur->lazy=0;
    }
}

void update(node *cur, int l, int r, int posl, int posr, int val){
    push_update(cur,l,r);
    if(l>r || l>posr || r<posl)return;
    else if(l>=posl && r<=posr){
        cur->lazy=val;
        push_update(cur,l,r);
    }
    else{
        int mid = (l+r)>>1;
        expand(cur,l,r);
        update(cur->left, l, mid, posl, posr, val);
        update(cur->right, mid+1, r, posl, posr, val);
        cur->data = min(cur->left->data, cur->right->data);
    }
}

int query(node *cur, int l, int r, int posl, int posr){
    push_update(cur,l,r);
    if(l>r || l>posr || r<posl)return INT_MAX;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    expand(cur,l,r);
    return min(query(cur->left, l, mid, posl, posr), query(cur->right, mid+1, r, posl, posr));
}



inline void solve(int caseNum){
	int k;
	cin>>n>>k;
	for(int i=0,x; i<n; i++){
		cin>>x;
		rmq.set(i,x);
	}

	rmq.init(n);

	int len = (n*k)-1;
	int q,qt,l,r,x;
	cin>>q;
	node *root = newNode(rmq.query(0,n-1), 0);

	while(q--){
		cin>>qt>>l>>r;
		if(qt==1){
			cin>>x;
			update(root,0,len,l-1,r-1,x);
		}
		else cout<<query(root,0,len,l-1,r-1)<<"\n";

	}
}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}