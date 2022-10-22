#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 4e5+5;

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

int firstOcc[N];
int secondOcc[N];
int diff[N];
ll occ[N];

inline void solve(int caseNum){
	string s,t;
	cin>>s>>t;
	int adsaf;
	cin>>adsaf;

	string xd = s+"#"+t;
	SA.init(xd);
	for(int i=0; i<xd.length(); i++){
		firstOcc[i]=0;
		secondOcc[i]=0;
		diff[i]=0;
		occ[i]=0;

		if(SA.SA[i]<s.length())firstOcc[i]=1;
		else if(xd[SA.SA[i]]!='#')secondOcc[i]=1;

		if(i>0){
			firstOcc[i] += firstOcc[i-1];
			secondOcc[i] += secondOcc[i-1];
		}
	}

	auto addOcc = [&](int l, int r, ll add)->void{
		occ[l]+=add;
		occ[r+1]-=add;
	};

	int offset=0;
	for(int i=0,rightmost; i<xd.length(); i++){
		offset+=diff[i];
		int low=i+1,high=xd.length()-1,mid;
		int minL=-1;

		while(low<=high){
			mid = (low+high)>>1;

			int aa=firstOcc[mid];
			if(i)aa-=firstOcc[i-1];
			int bb=secondOcc[mid];
			if(i)bb-=secondOcc[i-1];

			if(aa && bb){
				high=mid-1;
				minL=mid;
			}
			else low=mid+1;
		}

		if(minL==-1)continue;

		do{
			low=minL,high=xd.length()-1;
			rightmost=-1;
			while(low<=high){
				mid = (low+high)>>1;
				if(SA.lcp(i+1,mid)-offset > 0){
					low=mid+1;
					rightmost=mid;
				}
				else high=mid-1;
			}

			if(rightmost==-1)break;

			ll L = SA.lcp(i+1,rightmost);
			ll x = firstOcc[rightmost];
			ll y = secondOcc[rightmost];
			if(i){
				x-=firstOcc[i-1];
				y-=secondOcc[i-1];
			}

			addOcc(offset+1,L,x*y);
			diff[rightmost+1]-=(L-offset);
			offset=L;
		}while(rightmost!=-1);
	}

	//dbug("here\n");
	ll total=0;
	for(int i=1; i<=adsaf; i++){

		total+=occ[i];
		cout<<total<<" ";
	}
	cout<<"\n";

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