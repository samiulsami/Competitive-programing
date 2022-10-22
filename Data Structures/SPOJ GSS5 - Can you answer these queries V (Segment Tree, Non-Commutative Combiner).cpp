#include<bits/stdc++.h>
using namespace std;
 
const int N = 1e4+5;
 
struct data{
    int pref,suff,total,best;
    data(){}
    data(int pref, int suff, int total, int best):pref(pref),suff(suff),total(total),best(best){}
    data(int x){pref=suff=total=best=x;}
};
 
inline data Combine(data L, data R, bool b=0){
    data ret;
    ret.pref = max(L.pref, L.total + R.pref);
    ret.suff = max(R.suff, R.total + L.suff);
    ret.total = L.total + R.total;
    if(!b)ret.best = max({L.best, R.best, L.suff+R.pref, L.total, R.total, ret.total});
	else ret.best = max({L.suff+R.pref, L.total+R.pref, R.total+L.suff});
    return ret;
}
 
data Tree[4*N];
int arr[N];
 
void build(int node, int l, int r){
    if(l==r)Tree[node]=data(arr[l-1]);
    else{
        int mid = (l+r)>>1;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Tree[node] = Combine(Tree[node*2], Tree[node*2+1]);
    }
}
 
data query(int node, int l, int r, int posl, int posr){
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
	if(posl>mid)return query(node*2+1, mid+1, r, posl, posr);
	if(posr<=mid)return query(node*2, l, mid, posl, posr);
	return Combine(query(node*2, l, mid, posl, posr), query(node*2+1, mid+1, r, posl, posr));
}
 
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d",&n);
		for(int i=0; i<n; i++)scanf("%d",&arr[i]);
		build(1,1,n);
		int m;
		scanf("%d",&m);
		int l,r,ll,rr;
		while(m--){
			scanf("%d%d%d%d",&l,&ll,&r,&rr);
			if(r>ll){
				int ans = query(1,1,n,l,ll).suff;
				if(ll+1<r)ans+=query(1,1,n,ll+1,r-1).total;
				ans+=query(1,1,n,r,rr).pref;
				printf("%d\n",ans);
			}
			else{
				int ans = 0;
				if(r-1>=l)ans+=query(1,1,n,l,r-1).suff;
				ans+=query(1,1,n,r,rr).pref;
				int s=0;
				if(ll+1<=rr)s=query(1,1,n,ll+1,rr).pref;
				ans = max({ans, query(1,1,n,r,ll).best,  query(1,1,n,r,ll).suff + s});
				printf("%d\n",ans);
			}
		}
	}
return 0;
}