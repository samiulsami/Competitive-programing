#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<ll,ll> pll;
const int N = 3e5+5;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

orderSet<pll>Tree[4*N];
ll arr[N];


void build(int node, int l, int r){
    if(l==r){
        Tree[node].insert({arr[l],l});
        return;
    }
    int mid = (l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid+1,r);
    for(auto &x:Tree[node<<1])Tree[node].insert(x);
	for(auto &x:Tree[node<<1|1])Tree[node].insert(x);
}

int query(int node, int l, int r, int posl, int posr, int v){
    if(l>r || l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return Tree[node].order_of_key(pll(v-1,1e9));
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr, v) + query(node*2+1, mid+1, r, posl, posr, v);
}

void update(int node, int l, int r, int pos, ll newval){
	if(l>r || l>pos || r<pos)return;
	Tree[node].erase(pll(arr[pos],pos));
	Tree[node].insert(pll(newval,pos));
	if(l==r)return;
	int mid = (l+r)>>1;
	update(node<<1, l, mid,pos, newval);
	update(node<<1|1, mid+1, r, pos, newval);
}

int main(){
	//freopen("output.txt","w",stdout);
	int n,m,u,v,p,l,r,k;
	ll newval;
	scanf("%d%d%d",&n,&m,&u);
	for(int i=1; i<=n; i++)scanf("%lld",&arr[i]);
	build(1,1,n);
	
	while(m--){
		scanf("%d%d%d%d",&l,&r,&v,&p);
		k = query(1,1,n,l,r,v);
		newval = 1LL*u*k;
		newval/=1LL*(r-l+1);
		update(1,1,n,p,newval);
		arr[p]=newval;
	}
	
	for(int i=1; i<=n; i++){
		printf("%lld\n",arr[i]);
	}
return 0;
}