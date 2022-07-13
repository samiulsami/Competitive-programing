#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;

int n;

struct node{
	int v;
	int clipboard;
	int add;
	node(){
		clipboard=0;
		add=0;
	}
	node(int a, int b, int c){
		v=a;
		clipboard=b;
		add=c;
	}
	
	bool operator<(const node &nd)const{
		//return (add-clipboard)>(nd.add-nd.clipboard);
		if(add==nd.add)return clipboard<nd.clipboard;
		return add>nd.add;
	}
}dist[1000006];


inline void solve(int caseNum){
	int n,x;
	cin>>x>>n;
	
	priority_queue<node>pq;
	dist[x].add=0;
	pq.push(node(x,0,0));
	//for(int i=x+1; i<=n; i++)dist[i].add =  i-x;
	
	if(x!=0){
		dist[0].add = min(x, 3);
		pq.push(node(0,0,dist[0].add));
		//for(int i=1; i<=n; i++)dist[i].add = min(dist[i].add,dist[0].add + i);
	}
	
	int ans = abs(n-x);
	
	while(!pq.empty()){
		auto top = pq.top();
		pq.pop();
		
		int add = top.add;
		int u = top.v;
		int clipboard = top.clipboard;

		ans = min(ans,abs(n-u)+add);
		if(u==n)continue;
		int newadd,v,newclip;
		
		if(clipboard!=0){
			v = u+clipboard;
			newadd = add+2;
			newclip = clipboard;
			if(v>n){
				ans = min(ans, v-n+newadd);
			}
			else{
				node tmp(v,newclip,newadd);
				if(dist[v]<tmp){
					dist[v]=tmp;
					pq.push(tmp);
				}
			}
		}
		
		{
			node tmp(u+1,0,add+1);
			if(dist[u+1]<tmp){
				dist[u+1]=tmp;
				pq.push(tmp);
			}
		}
		
		if(u>0){
			node tmp(u-1,0,add+1);
			if(dist[u-1]<tmp){
				dist[u-1]=tmp;
				pq.push(tmp);
			}
		}
		
		
		newadd = add+6;
		newclip = u;
		v = u*2;
		if(v>n){
			ans = min(ans, v-n+newadd);
		}
		else{
			node tmp(v,newclip,newadd);
			if(dist[v]<tmp){
				dist[v]=tmp;
				pq.push(tmp);
			}
		}
		
		
	}
	
	
	cout<<ans<<"\n";
	
}

int main(){
	for(int i=0; i<=1000002; i++)dist[i].add=1e9;
   //ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
	int T=1;
	//cin>>T;
	for(int i=1; i<=T; i++)
		solve(i);
return 0;
}