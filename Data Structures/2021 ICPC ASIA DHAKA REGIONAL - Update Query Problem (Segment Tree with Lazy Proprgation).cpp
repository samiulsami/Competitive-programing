#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

struct{
	struct Data{
		int cnt[26];
		int lazy;
		Data(){fill(cnt,cnt+26,0);lazy=-1;}
		void clr(){
			fill(cnt,cnt+26,0);
			lazy=-1;
		}
	}Tree[4*N];

	int n;

	inline Data Combine(Data a, Data b){
		Data ret;
		for(int i=0; i<26; i++)
			ret.cnt[i] = a.cnt[i] + b.cnt[i];
		return ret;
	}

	inline void push_update(int node, int l, int r){
		if(Tree[node].lazy!=-1){
			int x = Tree[node].lazy;
			Tree[node].clr();
			Tree[node].cnt[x] = r-l+1;
			if(l!=r){
				Tree[node<<1].lazy = x;
				Tree[node<<1|1].lazy = x;
			}
			Tree[node].lazy=-1;
		}
	}
	void build(int node, int l, int r, const string &s){
		if(l==r){
			Tree[node].clr();
			Tree[node].cnt[s[l-1]-'a']=1;
		}
		else{
			int mid = (l+r)>>1;
			build(node<<1, l, mid,s);
			build(node<<1|1, mid+1, r,s);
			Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
		}
	}

	void init(const string &s){
		n = s.length();
		build(1,1,n,s);
	}

	void update(int l, int r, int c){update(1,1,n,l,r,c);}
	void update(int node, int l, int r, int posl, int posr, int c){
		push_update(node,l,r);
		if(l>r || r<posl || l>posr)return;
		if(l>=posl && r<=posr){
			Tree[node].lazy=c;
			push_update(node,l,r);
			return;
		}
		int mid = (l+r)>>1;
		update(node<<1, l, mid, posl, posr, c);
		update(node<<1|1, mid+1, r, posl, posr,c);
		Tree[node] = Combine(Tree[node<<1], Tree[node<<1|1]);
	}

	Data query(int l, int r){return query(1,1,n,l,r);}
	Data query(int node, int l, int r, int posl, int posr){
		push_update(node,l,r);
		if(l>=posl && r<=posr)return Tree[node];
		int mid = (l+r)>>1;
		if(posl>mid)return query(node<<1|1,mid+1,r,posl,posr);
		if(posr<=mid)return query(node<<1,l,mid,posl,posr);
		return Combine(query(node<<1,l,mid,posl,posr),query(node<<1|1,mid+1,r,posl,posr));
	}

}segtree[2];


inline void solve(int caseNum){
	string p,Q;
	cin>>p>>Q;
	segtree[0].init(p);
	segtree[1].init(Q);
	
	int q,qt,l1,r1,l2,r2;
	char c;
	cin>>q;

	while(q--){
		cin>>qt;
		if(qt==1){
			cin>>l1>>r1>>c;
			segtree[0].update(l1,r1,c-'a');
		}
		else if(qt==2){
			cin>>l2>>r2>>c;
			segtree[1].update(l2,r2,c-'a');
		}
		else{
			cin>>l1>>r1>>l2>>r2;
			auto X = segtree[0].query(l1,r1);
			auto Y = segtree[1].query(l2,r2);

			ll ans = 1LL*(r1-l1+2)*1LL*(r2-l2+2);
			for(int i=0; i<26; i++){
				ans -= (1LL*X.cnt[i]*Y.cnt[i]);
				//cout<<char(i+'a')<<": "<<X.cnt[i]<<" "<<Y.cnt[i]<<"\n";
			}
			cout<<ans<<"\n";
		}
	}

}

int main(){
	#ifdef idk123
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	ios_base::sync_with_stdio(0);cin.tie(0);
	int T=1;
	cin>>T;
	for(int i=1; i<=T; i++)solve(i);
return 0;
}