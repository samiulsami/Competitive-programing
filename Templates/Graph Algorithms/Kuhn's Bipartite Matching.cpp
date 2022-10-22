#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
/**
    Number of nodes in set U = n (numbered 0 to n-1)
    Number of nodes in set V = m (numbered n to n+m-1)
    bpm() returns maximum matching between set U and V
**/
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);


namespace Kuhn{
    const int MAX=2*50005;
    bool vis[MAX];
    vector<int>graph[MAX];
    int matchR[MAX];

    inline void addEdge(int u, int v){
        graph[u].push_back(v);
    }

    bool match(int x){
        if(vis[x])return 0;
        vis[x]=1;

        shuffle(graph[x].begin(),graph[x].end(),rng);
        for(int v:graph[x]){
            if(matchR[v]==-1){
                matchR[v]=x;
                return 1;
            }
        }

        for(int v:graph[x]){
            if(match(matchR[v])){
                matchR[v]=x;
                return 1;
            }
        }

        return 0;
    }

    int bpm(int n){
        int ret=0;
        memset(matchR,-1,sizeof(matchR));
        for(int i=1; i<=n; i++){
            memset(vis,0,sizeof(vis));
            if(match(i))ret++;
        }
        return ret;
    }
};

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);




return 0;
}
