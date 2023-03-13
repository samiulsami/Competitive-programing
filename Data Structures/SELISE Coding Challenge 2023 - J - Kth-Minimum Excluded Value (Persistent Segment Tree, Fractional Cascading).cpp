#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"


struct node{
    int data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
};
int nodeCnt=0;

inline node *newNode(int data=0, node *left=NULL, node *right=NULL){
    node *nn = new node(data,left,right);
    return nn;
}

void build(node *cur, int l, int r){
    if(l==r){
    	cur->data = 0;
    	return;
    }
    cur->left=newNode();
    cur->right=newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
    cur->data = cur->left->data + cur->right->data;
}

node *update(node *cur, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(val);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,val);
    tmp->right = update(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

int query(node *curL, node *curR, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return curR->data - curL->data;
    int mid = (l+r)>>1;
    if(posl>mid)return query(curL->right, curR->right, mid+1, r, posl, posr);
    if(posr<=mid)return query(curL->left, curR->left, l, mid, posl, posr);
    return query(curL->left, curR->left, l, mid, posl, posr) + query(curL->right, curR->right, mid+1, r, posl, posr);
}

int Find(node *L, node *R, int l, int r, int k){
	if(l==r)return l;
	int mid = (l+r)>>1;
	int lVal = mid-l+1;
	if(L && R->left)lVal += L->left->data;
	if(R && R->left)lVal -= R->left->data;

	if(lVal>=k)return Find(L->left, R->left, l, mid, k);
	return Find(L->right, R->right, mid+1, r, k-lVal);
}

const int lim = 1e6+1;
int maxval[500005];

inline void solve(int caseNum){
	int n,q;
	cin>>n;

	vector<node*>roots{newNode()};
	build(roots[0],1,lim);


	for(int i=1,x; i<=n; i++){
		cin>>x;
		roots.emplace_back(update(roots[i-1],1,lim,x,1));
		maxval[i] = max(maxval[i-1],x);
	}

	//dbug(roots[5]->data);
	cin>>q;
	int l,r,k;
	while(q--){
		cin>>l>>r>>k;
	
		if(l>r)swap(l,r);
		int mx = roots[r]->data - roots[l-1]->data;

		if(maxval[r]-mx<k){
			cout<<mx+k<<"\n";
			continue;
		}
		// int low=1,high=lim,mid,ans=-1;

		// while(low<=high){
		// 	mid = (low+high)>>1;
		// 	int cur = mid - query(roots[l-1],roots[r],1,lim,1,mid);

		// 	if(cur<k)low=mid+1;
		// 	else{
		// 		ans = mid;
		// 		high=mid-1;
		// 	}
		// }

		
		cout<<Find(roots[l-1],roots[r],1,lim,k)<<"\n";
		
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