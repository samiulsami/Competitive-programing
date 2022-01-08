#include<bits/stdc++.h>
/*
    Problem: LightOJ 1400 - Employment
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
#define xx first
#define yy second
#define pb push_back
#define mp make_pair
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0; i<=n; i++)
#define FORR(i,l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl
#define eikhane cout<<"Eikhane"<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template<typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const double PI = 2*acos(0.0);
const int MOD = 1e9+7;
const int MAX = 105;

list<int>candidate[MAX],company[MAX];
int matchL[MAX],matchR[MAX],preferenceTable[MAX][MAX];

inline void Solve(int Case){
    int n;
    si(n);
    FOR(i,n){
        candidate[i].clear();
        company[i].clear();
        matchL[i]=-1;
        matchR[i]=-1;
    }

    FOR(i,n-1){
        int x;
        FOR(j,n-1){
            si(x);
            candidate[i].pb(x-n-1);
        }
    }
    FOR(i,n-1){
        int x;
        FOR(j,n-1){
            si(x);
            company[i].pb(x-1);
            preferenceTable[i][x-1]=(n-j-1);
        }
    }

    bool done=0;

    while(!done){

        done=1;
        FOR(i,n-1){

            if(matchL[i]==-1){
                done=0;

                    int w = candidate[i].front();
                    candidate[i].pop_front();

                    int preference=preferenceTable[w][i];

                    if(matchR[w]==-1){
                        matchR[w]=i;
                        matchL[i]=w;
                    }
                    else if(preferenceTable[w][i]>preferenceTable[w][matchR[w]]){
                        matchL[matchR[w]] = -1;
                        matchR[w] = i;
                        matchL[i] = w;
                    }

            }
        }
    }

    pf("Case %d:",Case);

    FOR(i,n-1){
        pf(" (%d %d)", i+1, matchL[i]+n+1);
    }
    nl;
}

  #define Multiple_Test_Cases
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
