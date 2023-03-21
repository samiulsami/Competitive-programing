#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
const int N = 5e5+5;

struct node{
	node *l=NULL,*r=NULL;
	uint32_t prior = rng();
	int key,minval;
	node(){}
};
	
inline void update_cnt(node *t){if(t)t->minval = t->l ? t->l->minval : t->key;}
	
void split(node *t, node* &l, node* &r, int key){/// Subtree 'l' contains keys strictly less than 'key'
	if(!t)return void(l=r=NULL);
	if(key<=t->key)split(t->l, l, t->l, key), r=t;
	else split(t->r, t->r, r, key), l=t;
	update_cnt(t);
}
	
void merge(node* &t, node *l, node *r){
	if(!l || !r)t = l?l:r;
	else if(l->prior > r->prior)merge(l->r, l->r, r), t=l;
	else merge(r->l, l, r->l), t=r;
	update_cnt(t);
}

void insert(node* &t, node *u){
	if(!t)t=u;
	else if(u->prior > t->prior)split(t, u->l, u->r, u->key), t=u;
	else insert(t->key <= u->key ? t->r : t->l, u);
	update_cnt(t);
}

node *mp[102];
int arr[200005];

void dfs(node *cur, int val){
	if(!cur)return;
	if(cur->l)dfs(cur->l, val);
	if(cur->r)dfs(cur->r, val);
	arr[cur->key] = val;
}

inline void solve(int caseNum){
	int n;
	cin>>n;

	for(int i=1; i<=n; i++){
		cin>>arr[i];
		node *nd = new node();
		nd->key = i;
		nd->minval = i;
		insert(mp[arr[i]], nd);
		arr[i]=-1;
	}
	
	int q,l,r,x,y;
	cin>>q;

	while(q--){
		cin>>l>>r>>x>>y;
		if(x==y || !mp[x])continue;
		node *xm,*xr;
		split(mp[x],mp[x],xr,l);
		split(xr,xm,xr,r+1);
		merge(mp[x],mp[x],xr);
		
		if(!xm)continue;
		node *ym,*yr;

		split(mp[y],mp[y],yr,l);
		split(yr,ym,yr,r+1);///mp[y]:[1,l-1], yr:[r+1,n], ym:[l,r]

		node *hehe=NULL;

		while(xm){
			if(ym){
				node *lft;
				split(xm,lft,xm,ym->minval);
				merge(hehe,hehe,lft);
			}
			else{
				merge(hehe,hehe,xm);
				break;
			}

			if(xm){
				node *lft;
				split(ym,lft,ym,xm->minval);
				merge(hehe,hehe,lft);
			}
			else{
				merge(hehe,hehe,ym);
				break;
			}
		}

		merge(mp[y],mp[y],hehe);
		merge(mp[y],mp[y],yr);
	}
	
	for(int i=1; i<=100; i++)dfs(mp[i],i);
	for(int i=1; i<=n; i++)cout<<arr[i]<<" ";
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