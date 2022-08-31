#include<bits/stdc++.h>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+500;
///0 indexed
///Don't insert '#' at the beginning of the string
///LCP[i] is the LCP of SA[i] and SA[i-1]
///invSA[i] is the position of 'i' in the suffix array
///LCP of the substrings beginning at indices 'l' and 'r' = LCP(invSA[l]+1, invSA[r]) (swap l and r if invSA[l]<invSA[r])
///O(nlogn) Time and Memory

const int K=__lg(N)+2;
struct SuffixArray{///0 indexed
    int SA[N],LCP[N],invSA[N];
    int RA[N],c[N],n;
    int Table[K][N]={{0}};
    inline void countingSort(int k){
        int mx = 200200,i,j,sum;
		fill(c,c+mx+5,0);
		for(i=0; i<n; i++)c[i+k<n ? RA[i+k]:0]++;
		for(i=0,sum=0; i<mx; i++){j=c[i],c[i]=sum,sum+=j;}
		for(i=0; i<n; i++)invSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];
		for(i=0; i<n; i++)SA[i]=invSA[i];
    }
    void init(const vector<int> &s){
		int i,k,j;
		n = (int)s.size();
		auto cmp = [&](int &a, int &b)->bool{
			if(RA[a]^RA[b])return RA[a]<RA[b];
			return (a+k<n && b+k<n)?RA[a+k]<RA[b+k]:a>b;
		};
		for(i=0; i<n; i++)SA[i]=i,RA[i]=s[i];
		for(k=1; k<n; k<<=1){
			countingSort(k);
			countingSort(0);
			invSA[0]=1;
			for(i=1; i<n; i++)invSA[i]=invSA[i-1]+cmp(SA[i-1],SA[i]);
			for(i=0; i<n; i++)RA[SA[i]]=invSA[i];
			if(invSA[n-1]==n)break;
		}
		for(i=0; i<n; i++)invSA[SA[i]]=i;
		for(i=0,k=0; i<n; i++){
			if(invSA[i]==0)k=0;
			else{
				j=SA[invSA[i]-1];
				while(i+k<n && j+k<n && s[i+k]==s[j+k])k++;
				LCP[invSA[i]]=k;
				Table[0][invSA[i]]=k;
				if(k>0)k--;
				else k=0;
			}
		}
		//for(i=0; i<n; i++)cout<<setw(2)<<SA[i]<<", LCP: "<<LCP[i]<<" "<<s.substr(SA[i])<<endl;
		for(i=1; i<=K; i++)for(j=0; j+(1<<i)-1<n; j++)Table[i][j] = min(Table[i-1][j], Table[i-1][j+(1<<(i-1))]);
    }
    inline int lcp(int l, int r){
        int lg=__lg(r-l+1);
        return min(Table[lg][l],Table[lg][r-(1<<lg)+1]);
    }
}SA;


void brute(vector<string>arr, int k){
	map<string,int>mp;
	for(string s:arr){
		set<string>st;
		for(int i=1; i<=s.length(); i++){
			for(int j=0; j+i-1<s.length(); j++)st.insert(s.substr(j,i));
		}
		for(string x:st)mp[x]++;
	}

	cout<<"\nbrute: ";
	for(int i=0; i<sz(arr); i++){
		ll cur=0;
		for(int len=1; len<=sz(arr[i]); len++){
			for(int j=0; j+len-1<sz(arr[i]); j++){
				if(mp[arr[i].substr(j,len)]>=k)cur++;
			}
		}

		cout<<cur<<" ";
	}
	cout<<"\nbrute end\n";
}

int mark[N];
int sufflen[N]={0};
int mp[N];
//node *nodes[N];
int diff[N]={0};
ll occDiff[N]={0};
ll ans[N]={0};
int cnt[N]={0};

inline void solve(int caseNum){
	memset(mark,-1,sizeof(mark));
	memset(mp,-1,sizeof(mp));
	int n,k;
	cin>>n>>k;
	vector<int>s;
	int div=-1;
	//vector<string>arr;
	for(int i=0; i<n; i++){
		string t;
		cin>>t;
		//arr.push_back(t);
		for(int j=0; j<sz(t); j++){
			s.push_back(int(t[j]-'a'+10));
			mark[sz(s)-1]=i;
			//sufflen[sz(s)-1] = sz(t)-j;
		}
		if(i!=n-1)s.push_back(102+i);
		if(k==1){
			ll x = sz(t);
			ans[i] = (x*(x+1LL))/2LL;
		}
	}

	if(k==1){
		for(int i=0; i<n; i++)cout<<ans[i]<<" ";
			cout<<"\n";
		return;
	}

	SA.init(s);
	int len = sz(s);
	//nodes[len] = newNode();
	//build(nodes[len],0,len-1);

	// for(int i=len-1; i>=0; i--){
	// 	int cur = mark[SA.SA[i]];
	// 	if(cur==-1){
	// 		nodes[i] = nodes[i+1];
	// 		continue;
	// 	}

	// 	node *tmp = nodes[i+1];
	// 	if(mp[cur]!=-1)tmp = update(tmp,0,len-1,mp[cur],0);
	// 	tmp = update(tmp,0,len-1,i,1);
	// 	mp[cur]=i;
	// 	nodes[i] = tmp;
	// }

	int offset=0;
	int distinct=0;
	int rptr=0;

	for(int i=0; i<len; i++){
		offset+=diff[i];
		if(s[SA.SA[i]]>100)continue;
		int low,high,mid,rightmost;
		// cout<<i<<" "<<minL<<"\n";
		// dbug(query(nodes[i],0,len-1,i,minL));
		while(distinct<k && rptr<len){
			if(s[SA.SA[rptr]]>100)rptr++;
			else if(++cnt[mark[SA.SA[rptr++]]] == 1)distinct++;
		}

		//dbug(distinct);
		if(distinct<k)break;

		do{
			low = rptr-1,high=len-1,mid;
			rightmost=-1;
			while(low<=high){
				mid = (low+high)>>1;
				if(SA.lcp(i+1, mid) - offset > 0){
					low=mid+1;
					rightmost=mid;
				}
				else high=mid-1;
			}

			if(rightmost==-1)break;

			int toAdd = SA.lcp(i+1,rightmost)-offset;
			occDiff[i] += toAdd;
			occDiff[rightmost+1] -= toAdd;
			diff[rightmost+1] -= toAdd;
			offset+=toAdd;
			
		}while(rightmost!=-1);

		if(--cnt[mark[SA.SA[i]]]==0)distinct--;
		// occDiff[i] += (sufflen[SA.SA[i]]-offset);
		// occDiff[i+1] -= (sufflen[SA.SA[i]]-offset);
	}

	ll total=0;
	for(int i=0; i<len; i++){
		if(s[SA.SA[i]]>100)continue;
		total += occDiff[i];
		ans[mark[SA.SA[i]]] += total;
	}

	for(int i=0; i<n; i++)cout<<ans[i]<<" ";
	//cout<<"\n";
	//brute(arr,k);
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
