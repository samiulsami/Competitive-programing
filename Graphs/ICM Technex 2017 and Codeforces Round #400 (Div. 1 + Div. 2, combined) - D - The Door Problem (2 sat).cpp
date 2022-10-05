#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

int status[N];
vector<int>switches[N];

inline void solve(int caseNum){
	int n,m;
	cin>>n>>m;
	for(int i=1; i<=n; i++)cin>>status[i];

	for(int i=1; i<=m; i++){
		int x;
		cin>>x;
		for(int j=0,k; j<x; j++){
			cin>>k;
			switches[k].push_back(i);
		}
	}

	sat::init(m);
	for(int i=1; i<=n; i++){
		if(status[i])sat::XNOR(switches[i][0], switches[i][1]);
		else sat::XOR(switches[i][0], switches[i][1]);
	}

	vector<int>xd;
	if(sat::satisfy(xd))cout<<"YES\n";
	else cout<<"NO\n";
	
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