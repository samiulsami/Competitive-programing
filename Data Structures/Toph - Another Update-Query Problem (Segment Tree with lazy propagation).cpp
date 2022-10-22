#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

const int N = 1e5+5;
const int inv2 = 500000004;
int arr[N];

int lazy[4*N];
int Tree[2][4*N];

void build(int node, int l, int r){
	lazy[node]=0;
	if(l==r){
		Tree[0][node] = arr[l];
		Tree[1][node] = (1LL*arr[l]*l)%MOD;
	}
	else{
		int mid = (l+r)>>1;
		build(node<<1, l, mid);
		build(node<<1|1, mid+1, r);
		Tree[0][node] = (Tree[0][node<<1] + Tree[0][node<<1|1])%MOD;
		Tree[1][node] = (Tree[1][node<<1] + Tree[1][node<<1|1])%MOD;
	}
}

inline void push_update(int node, int l, int r){
	if(lazy[node]){
		lazy[node]%=MOD;
		Tree[0][node] += (1LL*(r-l+1)*lazy[node])%MOD;
		Tree[0][node]%=MOD;
		
		int cur = ((1LL*r*(r+1))/2)%MOD;
		cur -= ((1LL*l*(l-1))/2)%MOD;
		if(cur<0)cur+=MOD;
		cur = (1LL*cur*lazy[node])%MOD;
		Tree[1][node] += cur;
		Tree[1][node]%=MOD;
		if(l^r){
			lazy[node<<1]+=lazy[node];
			lazy[node<<1]%=MOD;
			lazy[node<<1|1]+=lazy[node];
			lazy[node<<1|1]%=MOD;
		}
		
		lazy[node]=0;
	}
}

void update(int node, int l, int r, int posl, int posr, int x){
	push_update(node,l,r);
	if(l>r || l>posr || r<posl)return;
	if(l>=posl && r<=posr){
		lazy[node]+=x;
		lazy[node]%=MOD;
		push_update(node,l,r);
	}
	else{
		int mid = (l+r)>>1;
		update(node<<1, l, mid, posl, posr, x);
		update(node<<1|1, mid+1, r, posl, posr, x);
		Tree[0][node] = (Tree[0][node<<1] + Tree[0][node<<1|1])%MOD;
		Tree[1][node] = (Tree[1][node<<1] + Tree[1][node<<1|1])%MOD;
	}
}

void query(int node, int l, int r, int posl, int posr, int &a, int &b){
	push_update(node,l,r);
	if(l>r || l>posr || r<posl)return;
	if(l>=posl && r<=posr){
		a+=Tree[0][node];
		if(a>=MOD)a-=MOD;
		b+=Tree[1][node];
		if(b>=MOD)b-=MOD;
	}
	else{
		int mid = (l+r)>>1;
		if(posl>mid)query(node<<1|1, mid+1, r, posl, posr, a,b);
		else if(posr<=mid)query(node<<1, l, mid, posl, posr, a,b);
		else{
			query(node<<1|1, mid+1, r, posl, posr, a,b);
			query(node<<1, l, mid, posl, posr, a,b);
		}
	}
}

int main(){
	int T,n,q,c,l,r,x,tmp,ans;
	scanf("%d", &T);
	
	for(int cas=1; cas<=T; cas++){
		printf("Case %d:\n",cas);
		
		scanf("%d%d",&n,&q);
		for(int i=1; i<=n; i++)scanf("%d",&arr[i]);
		build(1,1,n);
		
		while(q--){
			scanf("%d%d%d%d",&c,&l,&r,&x);
			
			if(c==1)update(1,1,n,l,r,x);
			else{
				ans=0;
				tmp=0;
				query(1,1,n,l,r,tmp,ans);
				ans -= (1LL*(l)*tmp)%MOD;
				if(ans<0)ans+=MOD;
				ans = (1LL*ans*x)%MOD;
				ans += tmp;
				if(ans>=MOD)ans-=MOD;
				printf("%d\n",ans);
			}
		}
	}
	
	return 0;
}