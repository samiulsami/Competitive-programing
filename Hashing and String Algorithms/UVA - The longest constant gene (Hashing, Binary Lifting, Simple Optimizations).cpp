#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());

const int mod1 = (1LL<<31)-1;
const int base = 1521+rng()%(1<<22);
int P[1000005];

inline int mod(ll x) {
    if(x<mod1)return x;
    x+=mod1;
    x=(x>>31)+(x&mod1);
    return int((x>>31)+(x&mod1));
}

struct Hash{///1 indexed
    vector<int>H;
    int n;
    Hash(){}
    Hash(const string &s){
        n = int(s.size());
        H.resize(n+1);H[0]=0;
        for(int i=0; i<n; i++)
            H[i+1] = mod((1LL*H[i]*base) + ((ll)s[i]));
    }
    inline int fHash(int l, int r){
        int h = H[r] - mod(1LL*H[l-1] * P[r-l+1]);
        return (h<0?h+mod1:h);
    }
    bool operator<(const Hash &H)const{return n<H.n;}
};

inline void solve(int caseNum){
	int n;
	cin>>n;
	int minlen=int(1e9);
	Hash H[n+1];
	
	for(int i=0; i<n; i++){
		string s;
		cin>>s;
		H[i] = Hash(s);
		minlen = min(minlen, (int)s.length());
	}
	sort(H, H+n);
	int minstart=0;
	while((1<<minstart)<minlen)minstart++;

	int ans=0;

	for(int k=minstart; k>=0; k--){
		int cur = ans|(1<<k);
		bool possible=1;
		vector<int>hashes;

		for(int j=1; j+cur-1<=H[0].n; j++)hashes.push_back(H[0].fHash(j,j+cur-1));
		if(hashes.empty())continue;

		sort(all(hashes));
		hashes.erase(unique(all(hashes)), hashes.end());

		for(int x=1; x<n; x++){
			possible=0;
			vector<int>newHash;

			for(int j=1,curhash; j+cur-1<=H[x].n; j++){
				curhash = H[x].fHash(j,j+cur-1);
				if(binary_search(all(hashes), curhash)){
					possible=1;
					newHash.push_back(curhash);
				}
			}

			if(!possible)break;
			if(newHash.empty())break;
			swap(hashes, newHash);
			sort(all(hashes));
			hashes.erase(unique(all(hashes)), hashes.end());
		}


		if(possible)ans|=(1<<k);
	}

	cout<<ans<<"\n";
}

int main(){
	P[0]=1;
	for(int i=1; i<=1000001; i++)P[i] = mod(1LL*P[i-1]*base);
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