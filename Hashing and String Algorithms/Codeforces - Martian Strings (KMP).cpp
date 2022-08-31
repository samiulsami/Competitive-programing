#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

vector<int> kmp(const string &s){
    vector<int>pi((int)s.size(),0);
    for(int i=1,j=0; i<(int)s.size(); i++){
        j=pi[i-1];
        while(j && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
    }
    return pi;
}

inline void solve(int caseNum){
	string s;
	cin>>s;

	int m;
	int ans=0;
	string x;
	cin>>m;

	while(m--){
		cin>>x;
		int n = x.length();
		if(n==1)continue;
		vector<int>pref(n+1,int(1e9));///pref[i] = leftmost prefix of size i
		vector<int>suff(n+1,-1);///suff[i] = rightmost suffix of size i
		vector<int>pi = kmp(x);

		for(int i=0,j=0; i<s.length(); i++){
			while(j && s[i]!=x[j])j = pi[j-1];
			if(s[i]==x[j])j++;
			if(j)pref[j] = min(pref[j], i-j+1);
			if(j==x.length())j=pi[j-1];
		}

		reverse(all(x));
		pi = kmp(x);

		for(int i=s.length()-1,j=0; i>=0; i--){
			while(j && s[i]!=x[j])j = pi[j-1];
			if(s[i]==x[j])j++;
			if(j)suff[j] = max(suff[j], i+j-1);
			if(j==x.length())j=pi[j-1];
		}

		bool found = bool(pref[x.length()] != int(1e9) || suff[x.length()] != -1);

		for(int i=1; !found && i<=x.length(); i++){
			if(pref[i]==int(1e9))continue;
			int req = x.length()-i;
			if(suff[req]==-1)continue;

			if(suff[req]-req>=pref[i]+i-1){
				found=1;
				//cout<<pref[i]<<" "<<suff[req]<<endl;
			}
		}

		// for(int i=1; i<=x.length(); i++){
		// 	cout<<i<<": "<<pref[i]<<" "<<suff[i]<<endl;
		// }

		if(found){
			//reverse(all(x));
			//cout<<"Found: "<<x<<endl;
			ans++;
		}
	}

	cout<<ans;
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