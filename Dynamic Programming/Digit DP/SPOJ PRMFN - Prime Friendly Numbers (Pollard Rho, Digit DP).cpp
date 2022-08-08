#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 2e5+5;

int dp[20][10][2];
vector<int>num;
vector<int>digits{0,2,3,5,7};

int f(int i, bool flag, bool z, int last){
    if(i==-1)return (z && last!=2 && last!=5);
    int &ret = dp[i][last][z];
    if(~ret && !flag)return ret;
    int cur=0;

    for(int j:digits){
        if(z && j==0)continue;
        if(flag && j>num[i])continue;
        cur |= f(i-1, num[i]==j?flag:0, z||(j>0), j);
    }

    if(!flag)ret=cur;
    return cur;
}

ll prnt(int i, bool flag, bool z, int last, ll ans){
    if(i==-1)return ans;
    for(int j=4,x; j>=0; j--){
        x=digits[j];
        //if(z && x==0)continue;
        if(flag && x>num[i])continue;
        if(f(i-1, num[i]==x?flag:0, z||(x>0), x)){
            return prnt(i-1, num[i]==x?flag:0, z||(x>0), x, (ans*10LL)+x);
        }
    }
    return 0;
}

ll getPrev(ll n){
    num.clear();
    while(n)num.push_back(n%10),n/=10;
    return prnt(int(num.size())-1, 1, 0, 0, 0);
}

namespace PollardRho{///Kactl Pollard Rho and Miller Rabin
    vector<uint64_t>bases{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    mt19937_64 rng64((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
 
    inline int64_t modmul(uint64_t a, uint64_t b, uint64_t mod){
        ///Works for numbers less than 2^63 or ~9e18
        int64_t ret = a * b - mod * (uint64_t)(1.0L / mod * a * b);
        return ret + mod * (ret < 0) - mod * (ret >= (int64_t) mod);
    }
 
    int64_t modpow(int64_t a, int64_t b, int64_t MOD){
        if(b==0)return 1;
        if(b==1)return a%MOD;
        int64_t ret=1;
        a%=MOD;
        while(b>0){
            if(b&1)ret=modmul(ret,a,MOD);
            b>>=1;
            a=modmul(a,a,MOD);
        }
        return ret%MOD;
    }
 
    bool isPrime(int64_t n) {
        ///Guaranteed to work for integers up to 7e18
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        uint64_t s = __builtin_ctzll(n-1), d = n >> s;
        auto check = [&](uint64_t a)->bool{
            uint64_t p = modpow(a%n, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = modmul(p, p, n);
            if (p != n-1 && i != s) return 1;
            return 0;
        };
        for (uint64_t a : bases)
            if(check(a))return 0;
        return 1;
    }
 
    uint64_t fastgcd(int64_t a, int64_t b) {
        if (!a || !b)
            return a | b;
        uint64_t shift = __builtin_ctzll(a | b);
        a >>= __builtin_ctzll(a);
        do {
            b >>= __builtin_ctzll(b);
            if (a > b)swap(a,b);
            b -= a;
        } while (b);
        return a << shift;
    }
 
    
    uint64_t pollard(uint64_t n) {
        uint64_t c = 1, x = 0, y = 0, t = 0, prod = 2, x0 = 1, q;
        auto f = [&](uint64_t X)->uint64_t{ return modmul(X, X, n) + c;};
        while (t++ % 40 or fastgcd(prod, n) == 1) {
            if (x == y) c = rng64()%(n-1)+1, x = x0, y = f(x);
            if ((q = modmul(prod, max(x, y) - min(x, y), n))) prod = q;
            x = f(x), y = f(f(y));
        }
        return fastgcd(prod, n);
    }
 
    vector<int64_t> PrimeFactorize(int64_t n){///~O(n^(1/4))
        if(n==1)return {};
        if(isPrime(n))return {n};
        int64_t factor = pollard(n);
        vector<int64_t> a = PrimeFactorize(factor), b = PrimeFactorize(n/factor);
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
 
    vector<int64_t> Factorize(int64_t n){///~O(n^(1/3))
        auto primeFactors = PrimeFactorize(n);
        sort(primeFactors.begin(), primeFactors.end());
        vector<int64_t>ret;
        for(int x=0,prevCount,cnt; x<(int)primeFactors.size(); x++){
            cnt=1;
            while(x+1<int(primeFactors.size()) && primeFactors[x+1]==primeFactors[x])x++,cnt++;
            prevCount = int(ret.size());
            for(int j=0; j<cnt; j++)
                for(int k=0,curSize=(int)ret.size(); k<prevCount; k++)
                    ret.push_back(ret[curSize - prevCount + k]*primeFactors[x]);
            ret.push_back(primeFactors[x]);
            for(int i=1; i<cnt; i++)
                ret.push_back(ret[int(ret.size())-1]*primeFactors[x]);
        }
        ret.push_back(1);
        return ret;
    }
};

inline void solve(int caseNum){
    ll n;
    cin>>n;
    ll ans=100;
    if(n<=10){
        if(n>=7)ans=7;
        else if(n>=5)ans=5;
        else if(n>=3)ans=3;
        else ans=2;
    }
    else{
        n = getPrev(n);
        while(!PollardRho::isPrime(n))
            n = getPrev(n-1);
        ans=n;
    }
    cout<<"Case "<<caseNum<<": "<<ans<<"\n";

}

int main(){
    memset(dp,-1,sizeof(dp));
    #ifdef idk123
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
    int T=1;
    cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);
return 0;
}