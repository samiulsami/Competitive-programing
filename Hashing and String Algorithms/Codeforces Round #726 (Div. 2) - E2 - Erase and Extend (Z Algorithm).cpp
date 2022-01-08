#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl;
#define dbug(x) cerr<<"dbug: "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
const int N = 1e5+5;

vector<int> Z_Algo(const string &s){
	int n = (int)s.size();
	vector<int>Z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)Z[i]=min(r-i+1,Z[i-l]);
		while(i+Z[i]<n && s[Z[i]]==s[i+Z[i]])Z[i]++;
		if(i+Z[i]-1>r)l=i,r=i+Z[i]-1;
	}
	return Z;
}



void solve(int caseno){
    int n,k;
    string s;
    cin>>n>>k;
    cin>>s;

	vector<int> z = Z_Algo(s);

    int st=1;
    bool found=0;
    for(int i=1; i<sz(s); i++){
        if(i+z[i]>=n || (s[z[i]]<=s[i+z[i]])){
            st=i;
            found=1;
            break;
        }

    }
    //dbug(st);
    if(found)s.erase(s.begin()+st,s.end());
    //cout<<s<<endl;
    while(sz(s)<k)s+=s;
    while(sz(s)>k)s.pop_back();
    cout<<s<<endl;


}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T=1;
    //scanf("%d",&T);

    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}