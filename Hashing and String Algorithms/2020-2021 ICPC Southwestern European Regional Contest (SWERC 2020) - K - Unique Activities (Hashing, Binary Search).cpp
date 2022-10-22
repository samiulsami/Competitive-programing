#include<bits/stdc++.h>
using namespace std;

typedef uint64_t ull;

const ull mod1 = (1ull<<61) - 1;
inline ull hashmodmul(ull a, ull b){
	ull l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	ull ret = (l&mod1) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod1) + (ret>>61);
	ret = (ret & mod1) + (ret>>61);
	return ret-1;
}
inline ull hashAdd(ull a, ull b){a+=b;return a>=mod1?a-mod1:a;}
inline ull hashSub(ull a, ull b){a-=b;return a>=mod1?a+mod1:a;}
const ull base1 = 17423;
vector<ull>P{1};

struct Hash{
    vector<ull>H;
    int n;
    Hash(){}
    template<typename T>
    Hash(const T &s, int n):n(n),H(n+1){
        while((int)P.size()<=n)P.push_back(hashmodmul(base1,P.back()));
        for(int i=0; i<n; i++)
            H[i+1] = hashAdd(hashmodmul(H[i], base1), (ull)s[i]);
    }
    ull getHash(int l, int r){return hashSub(H[r], hashmodmul(H[l-1], P[r-l+1]));}
};

char s[300005];

int main(){
    P.reserve(300000);
    scanf(" %s",&s);
    int n = strlen(s);
    Hash H(s,n);

    int low=1,high=n,mid;
    int anslen=n,ansind=INT_MAX;
    ull tmphash;
    while(low<=high){
        mid = (low+high)>>1;
        unordered_map<ull,int>mp;
        unordered_map<ull,int>ind;
        mp.reserve(1024);
        mp.max_load_factor(0.25);
        ind.reserve(1024);
        ind.max_load_factor(0.25);
        for(int i=1; i+mid-1<=n; i++){
            tmphash=H.getHash(i,i+mid-1);
            if(!mp.count(tmphash))ind[tmphash]=i;
            mp[tmphash]++;
        }

        bool found=0;

        for(auto it:mp){
            if(it.second==1){
                if(mid<anslen){
                    anslen=mid;
                    ansind=ind[it.first];
                }
                else if(mid==anslen && ansind>ind[it.first]){
                    anslen=mid;
                    ansind=ind[it.first];
                }
                found=1;
            }
        }

        if(found)high=mid-1;
        else low=mid+1;
    }

    if(ansind==INT_MAX)printf("%s\n",s);
    else{
        for(int i=0; i<anslen; i++)printf("%c",s[i+ansind-1]);
        printf("\n");
    }

return 0;
}
