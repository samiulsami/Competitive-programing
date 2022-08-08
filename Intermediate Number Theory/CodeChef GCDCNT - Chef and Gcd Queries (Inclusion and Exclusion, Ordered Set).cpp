#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
///   Set.find_by_order(k)  returns a pointer to the k'th element (0 indexed)
///   Set.order_of_key(k)   returns an integer equal to the number of elements STRICTLY SMALLER than 'k'
template<typename T> using orderSet = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

const int primesN = 1e5+5;
int spf[primesN]={0};
vector<int>primes;

void sieve(){///O(primesN)
    for(int i=2; i<primesN; i++){
        if(spf[i]==0){
            spf[i]=i;
            primes.push_back(i);
        }
        for(int j=0; j<(int)primes.size() && primes[j]<=spf[i] && 1LL*i*primes[j]<primesN; j++)
            spf[i*primes[j]]=primes[j];
    }
}

vector<int> get(int n){
    vector<int>ret;
    while(n>1){
        int x = spf[n];
        ret.push_back(x);
        while(n%x==0)n/=x;
    }
    return ret;
}

orderSet<int>st[primesN];
int arr[50005];

inline void update(int ind, int v, bool flag){
    auto x = get(v);
    for(int mask=1,mx=(1<<sz(x)),val; mask<mx; mask++){
        val=1;
        for(int i=0; i<sz(x); i++)
            if(bool(mask&(1<<i)))val*=x[i];
        if(flag)st[val].insert(ind);
        else st[val].erase(ind);
    }
}

inline void solve(int caseNum){
    int n;
    cin>>n;
    for(int i=1; i<=n; i++){
        cin>>arr[i];
        update(i,arr[i],1);
    }

    int q,a,b,l,g;
    cin>>q;
    while(q--){
        cin>>a>>b>>l;
        if(a==1){
            update(b,arr[b],0);
            update(b,l,1);
            arr[b]=l;
        }
        else{
            cin>>g;
            auto pf = get(g);
            int ans = l-b+1;
            for(int mask=1,mx=(1<<sz(pf)),val; mask<mx; mask++){
                val=1;
                for(int i=0; i<sz(pf); i++)
                    if(bool(mask&(1<<i)))val*=pf[i];
                int cur = st[val].order_of_key(l+1)-st[val].order_of_key(b);
                if(__builtin_popcount(mask)&1)ans-=cur;
                else ans+=cur;
            }
            cout<<ans<<"\n";
        }
    }
}

int main(){
    sieve();
    #ifdef idk123
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
    int T=1;
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}