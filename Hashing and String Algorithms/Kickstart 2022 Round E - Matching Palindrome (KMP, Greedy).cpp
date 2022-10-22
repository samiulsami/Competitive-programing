#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

string kmp(string s, char x){
	string tmp = s;
	string r=s;
	s.push_back(x);
    reverse(r.begin(),r.end());
    s = r+"#"+s;
    int n = s.length();
    vector<int>pi(n+1);
    for(int i=1,j; i<n; i++){
        j=pi[i-1];
        while(j>0 && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
        else pi[i]=0;
    }
    int ind = pi[n-1];
    reverse(s.begin(),s.end());
    string ret;
    ret.push_back(x);
    s=tmp;
    for(int i=ind,len=s.length(); i<len; i++)ret.push_back(s[i]);
    return ret;
}

bool isPal(string &s){
	for(int i=0,j=s.length()-1;i<j;i++,j--){
		if(s[i]!=s[j])return 0;
	}
	return 1;
}

inline void solve(int caseNum){
		int n;
		string s;
		cin>>n>>s;
		cout<<"Case #"<<caseNum<<": ";
		string ans = s;
		for(char c='a'; c<='z'; c++){
			string cur = kmp(s,c);
			if(isPal(cur) && sz(cur)<sz(ans))ans=cur;
		}
		cout<<ans<<"\n";
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