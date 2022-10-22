#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

///0 indexed
///Don't insert '#' at the beginning of the string
///LCP[i] is the LCP of SA[i] and SA[i-1]
///invSA[i] is the position of 'i' in the suffix array
///LCP of the substrings beginning at indices 'l' and 'r' = LCP(invSA[l]+1, invSA[r]) (swap l and r if invSA[l]<invSA[r])
///O(nlogn) Time and Memory

const int K=__lg(N)+2;
struct SuffixArray{///0 indexed
    int SA[N],LCP[N],invSA[N];
    int RA[N],c[N+200],n;
    int Table[K][N]={{0}};
    inline void countingSort(int k){
        int mx = max(130,n),i,j,sum;
		fill(c,c+mx+5,0);
		for(i=0; i<n; i++)c[i+k<n ? RA[i+k]:0]++;
		for(i=0,sum=0; i<mx; i++){j=c[i],c[i]=sum,sum+=j;}
		for(i=0; i<n; i++)invSA[c[SA[i]+k<n?RA[SA[i]+k]:0]++]=SA[i];
		for(i=0; i<n; i++)SA[i]=invSA[i];
    }
    void init(const string &s){
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

int brute(string s, int x){
	int ret=0;
	for(int len=1; len<=s.length(); len++){
		for(int i=0; i+len-1<s.length(); i++){
			int occ=0;
			string t = s.substr(i,len);
			for(int j=0; j+len-1<s.length(); j++){
				if(s.substr(j,len)==t)occ++;
			}

			if(occ>=x)ret++;
		}
	}
	return ret;
}

int diff[N];

inline void solve(int caseNum){
	string s;
	cin>>s;
	SA.init(s);

	int n = s.length();
	fill(diff,diff+n+1,0);

	int offset=0;
	vector<pair<int,ll> >occ;///{number of occurences, number of substrings with this number of occurences}

	for(int i=0,rightmost; i<n; i++){
		offset+=diff[i];

		do{
			int low=i+1,high=n-1,mid;
			rightmost=-1;
			while(low<=high){
				mid = (low+high)>>1;
				if(SA.lcp(i+1,mid)-offset>0){
					low=mid+1;
					rightmost=mid;
				}
				else high=mid-1;
			}

			if(rightmost==-1){
				occ.push_back({1,n-SA.SA[i]-offset});
				//if(occ.back().second<=0)occ.pop_back();
				break;
			}

			int L = SA.lcp(i+1,rightmost)-offset;
			//cout<<i<<" "<<rightmost<<" "<<L<<endl;
			occ.push_back({rightmost-i+1, 1LL*(L)*(rightmost-i+1)});
			offset+=L;
			diff[rightmost+1]-=L;
		}while(rightmost!=-1);
	}

	sort(all(occ));
	for(int i=sz(occ)-2; i>=0; i--)occ[i].second += occ[i+1].second;

	int k,x;
	cin>>k;
	while(k--){
		cin>>x;

		int low=0,high=sz(occ)-1,mid,ind=-1;
		while(low<=high){
			mid = (low+high)>>1;
			if(occ[mid].first>=x){
				ind=mid;
				high=mid-1;
			}
			else low=mid+1;
		}

		//cout<<"ME: ";
		if(ind==-1)cout<<"0\n";
		else cout<<occ[ind].second<<"\n";
		//cout<<"Brute: "<<brute(s,x)<<"\n";
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