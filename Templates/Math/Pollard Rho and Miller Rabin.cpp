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