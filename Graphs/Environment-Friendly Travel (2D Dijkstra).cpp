#include<bits/stdc++.h>
/*
    Problem: 2019-2020 ICPC Southwestern European Regional Programming Contest (SWERC 2019-20) - A. Environment-Friendly Travel
    Verdict: AC
*/
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

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
#define FOR(n) for(int i=0; i<=n; i++)
#define FORR(l,r) for(int i=l; i<=r; i++)
#define dbug(x) cout<<"dbug: "<<x<<endl

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> Set;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> Multiset;

template <typename T1, typename T2> inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& p){return os << "(" << p.first << ", " << p.second << ")";}
template<typename T> inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v){bool first = true; os << "["; for(unsigned int i = 0; i < v.size(); i++) { if(!first) os << ", "; os << v[i]; first = false; } return os << "]"; }
template<typename T>inline std::ostream &operator << (std::ostream & os,const std::set<T>& v){bool first = true;os << "[";for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii;first = false;}return os << "]";}
template<typename T1, typename T2>inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v){bool first = true;os << "[";for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii){if(!first)os << ", ";os << *ii ;first = false;}return os << "]";}

///------------------------------------------------------TEMPLATE END------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const int MAX = 1e5+5;
const double PI = 2*acos(0.0);

pii house;
pii dest;
int B;
int C[105];

struct node{
    int v,km,transport,cost;
    node(){}
    bool operator<(const node &nd)const{
        if(cost==nd.cost)return km>nd.km;
        return cost>nd.cost;
    }
};

vector<node>graph[1005];
pii station[1005];
ll dist[1004][104];

inline int Dist(int i, int j){
    pii a = station[i];
    pii b = station[j];
    int x = a.xx-b.xx;
    int y = a.yy-b.yy;
    double ret = (x*x)+(y*y);
    ret = ceil(sqrt(ret));

    return (int)ret;
}

inline void Solve(int Case){
    sii(house.xx,house.yy);
    sii(dest.xx,dest.yy);
    //cout<<Dist(0,1);
    si(B);
    si(C[0]);

    int TT,n;
    si(TT);
    for(int i=1; i<=TT; i++)si(C[i]);

    si(n);
    //bool targetInc=0;
    //int ind=0;
    for(int i=0,x,y,l; i<n; i++){
        siii(x,y,l);
        //if(x==dest.xx && y==dest.yy){
        //    targetInc=1;
       //     ind=i;
       // }
        station[i]={x,y};
        for(int j=0; j<l; j++){
            sii(x,y);
            node nd;
            nd.v=x;
            nd.transport=y;
            nd.cost=-1;
            graph[i].push_back(nd);
            nd.v=i;
            graph[x].push_back(nd);
        }
    }

    int S=n++;
    station[S]={house.xx,house.yy};
    int T=n++;
    station[T]={dest.xx,dest.yy};
    /*if(!targetInc){
        n++;
        station[n-1]={dest.xx,dest.yy};
        ind=n-1;
    }*/

    for(int i=0; i<n; i++){
        if(i==S)continue;
        node nd;
        nd.v=S;
        nd.km=Dist(i,S);
        nd.cost = nd.km*C[0];
        nd.transport=0;
        graph[i].push_back(nd);
        nd.v=i;
        graph[S].push_back(nd);
    }

    for(int i=0; i<n; i++){
        if(i==T)continue;
        node nd;
        nd.v=T;
        nd.km=Dist(i,T);
        nd.transport=0;
        nd.cost = nd.km*C[0];
        graph[i].push_back(nd);
        nd.v=i;
        graph[T].push_back(nd);
    }

    for(int i=0; i<n; i++){
        for(node &nd:graph[i]){
            //if(nd.cost!=-1)continue;
            nd.km = Dist(i,nd.v);
            nd.cost = nd.km*C[nd.transport];
        }
    }

    memset(dist,-1,sizeof(dist));
    dist[0][0]=0;
    node nd;
    nd.cost=0;
    nd.v=S;
    nd.km=0;
    priority_queue<node>pq;
    pq.push(nd);

    while(!pq.empty()){
        node u = pq.top();
        pq.pop();
        ll u_cst = u.cost;
        ll u_km = u.km;
        //if(dist[u.v][u_km]!=-1 && dist[u.v][u_km]<u_cst)continue;
        for(int i=0; i<(int)graph[u.v].size(); i++){
            node edge = graph[u.v][i];
            int v = edge.v;
            int v_cst = edge.cost;
            ll v_km = edge.km;
            ll newkm = u_km+v_km;
            if(newkm>B)continue;

            if(dist[v][newkm]==-1 || (dist[v][newkm] > u_cst + v_cst)){
                dist[v][newkm] = u_cst+v_cst;
                node newNode;
                newNode.v=v;
                newNode.cost = u_cst+v_cst;
                newNode.km = newkm;
                pq.push(newNode);
                //cout<<"u_cst: "<<u_cst<<", v_cst: "<<v_cst<<endl;
            }
        }
    }

    ll ans=LLONG_MAX;
    for(int i=0; i<=B; i++){
        if(dist[T][i]!=-1)ans=min(ans,dist[T][i]);
    }

    if(ans==LLONG_MAX)pf("-1\n");
    else pf("%lld\n",ans);
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
