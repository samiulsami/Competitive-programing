#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cerr<<"Value of "<<#x<<": "<<x<<"\n"

const int N = 2e5+5;

/**
    Hopcroft-Karp Bipartite Matching.
    Based on:
    http://zobayer.blogspot.com/2010/05/maximum-matching.html
    https://en.wikipedia.org/wiki/Hopcroft-Karp_algorithm

    Number of nodes in set U = n (numbered 0 to n-1)
    Number of nodes in set V = m (numbered n to n+m-1)

    Create a HopcroftKarp object with total number of nodes = (|U| + |V|)
    addEdge(x,y) adds a directed edge x-y
    bpm() returns maximum matching between set U and V
    Time complexity: O(sqrt(V)*E)
**/

struct HopcroftKarp{

    vector<vector<int> >graph;
    vector<int>matchL,matchR;
    vector<int>dist;
    int n;

    HopcroftKarp(int n):n(n),graph(n),matchL(n),matchR(n),dist(n){}

    void addEdge(int u, int v){
        graph[u].push_back(v);
    }

    bool bfs(){
        queue<int>q;
        for(int i=0; i<n; i++){
            if(matchL[i]==-1){
                dist[i]=0;
                q.push(i);
            }
            else dist[i]=-1;
        }
        bool flag=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v:graph[u]){
                if(matchR[v]==-1)flag=1;
                else if(dist[matchR[v]] == -1){
                    dist[matchR[v]] = dist[u]+1;
                    q.push(matchR[v]);
                }
            }
        }
        return flag;
    }

    bool dfs(int u){
        for(int v:graph[u]){
            if(matchR[v]==-1 || (dist[matchR[v]] == dist[u]+1 && dfs(matchR[v]))){
                matchR[v]=u;
                matchL[u]=v;
                return true;
            }
        }
        dist[u]=-1;
        return false;
    }

    int bpm(){
        int matching=0;
        for(int i=0; i<n; i++)matchL[i]=matchR[i]=-1;
        while(bfs()){
            for(int i=0; i<n; i++){
                if(matchL[i]==-1 && dfs(i))
                    matching++;
            }
        }
        return matching;
    }
};

inline bool check(string a, string b){
	int n = a.length();
	//assert(a!=b);
	//cout<<a<<"\n";
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			swap(a[i],a[j]);
			if(a==b)return 1;
			swap(a[i],a[j]);
		}
	}
	//cout<<a<<"\n";
	return 0;
}

int bruteforce(vector<string>arr){
	int ans=0;
	int n = sz(arr);
	for(int mask=1,mx=(1<<n);mask<mx; mask++){
		vector<string>tmp;
		for(int i=0; i<n; i++){
			if(bool(mask&(1<<i)))tmp.push_back(arr[i]);
		}

		bool pos=1;
		for(int i=0; pos &&i<sz(tmp); i++){
			for(int j=i+1; j<sz(tmp); j++)
				if(check(tmp[i],tmp[j])){
					pos=0;
					break;
				}
		}
		if(pos)ans = max(ans, __builtin_popcount(mask));
	}
	return ans;
}


inline void solve(int caseNum){
	int n;
	cin>>n;
	HopcroftKarp hk(n);

	vector<string>arr(n);
	for(int i=0; i<n; i++){
		cin>>arr[i];
		for(int j=0; j<i; j++)
			if(check(arr[j],arr[i])){
				hk.addEdge(j,i);
				hk.addEdge(i,j);
			}
	}

	//cerr<<"here\n";
	cout<<n-hk.bpm()/2<<"\n";
		//cout<<"bruteforce: "<<bruteforce(arr)<<"\n";
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