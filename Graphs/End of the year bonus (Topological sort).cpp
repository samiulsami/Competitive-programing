#include<bits/stdc++.h>
/*
    Problem: 2020 ICPC Gran Premio de Mexico 3ra Fecha - E.End of the year bonus
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
#define FF first
#define SS second
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<n; i++)
#define dbug(x) cerr<<"dbug: "<<x<<"\n"
#define CHK cerr<<"----------------\nCAME HERE\n----------------\n";

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 1e5+5;

vi graph[MAX];
ll arr[MAX];
int indeg[MAX]={0};

inline void Solve(int Case){
    ll n,b;
    cin>>n>>b;
    FOR(i,n)cin>>arr[i];

    for(int i=0; i<n; i++){
        int u=i,v=(i+1)%n;
        if(arr[u]<arr[v])graph[u].push_back(v),indeg[v]++;
        else if(arr[v]<arr[u])graph[v].push_back(u),indeg[u]++;
    }

    queue<int>q;
    for(int i=0; i<n; i++){
        if(indeg[i]==0){
            if(arr[i]!=0)arr[i]=1;
            q.push(i);
        }
        else arr[i]=0;
    }


    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int v:graph[u]){
            q.push(v);
            arr[v]=max(arr[v],arr[u]+1);
        }
    }

    for(int i=0; i<n; i++){
        cout<<(1LL*arr[i])*b;
        if(i!=n-1)cout<<" ";
    }
    cout<<endl;

}

  //#define Multiple_Test_Cases
int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    #ifdef Multiple_Test_Cases
        //cin>>T;
        si(T);
        for(int Case=1; Case<=T; Case++)
            Solve(Case);
    #else
        Solve(0);
    #endif

return 0;
}
