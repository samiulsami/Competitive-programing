#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}

const int N=2e5+5;
const int MOD=(1LL<<31)-1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};
int P[N];
char s[N];
int n;

inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

struct segTree{
    int n;
    bool isReverse;
    vector<int>Tree;

    segTree(int n, bool isReverse):n(n),isReverse(isReverse),Tree(2*n){}

    void update(int ind, int c){/// 0 indexed
        if(isReverse)Tree[ind+n] = mod(1LL*c*P[n-ind-1]);
        else Tree[ind+n] = mod(1LL*c*P[ind]);
        ind+=n;
        for(;ind>1; ind>>=1)Tree[ind>>1] = mod(1LL*Tree[ind]+1LL*Tree[ind^1]);
    }

    int query(int l, int r){///0 indexed
        if(l>r)return 0;
        if(l<0 || r<0 || l>=n || r>=n)return 0;
        l+=n;
        r+=n+1;
        int ret=0;
        for(;l<r; l>>=1,r>>=1){
            if(l&1)ret=mod(1LL*ret+1LL*Tree[l++]);
            if(r&1)ret=mod(1LL*ret+1LL*Tree[--r]);
        }
        return ret;
    }

    inline int getHash(int l, int r){///1 indexed
        if(l>r)return 0;
        if(l<=0 || r<=0 || l>n || r>n)return 0;
        l--,r--;
        if(isReverse)return mod(1LL*query(l,r)*P[l]);
        return mod(1LL*query(l,r)*P[n-r-1]);
    }
};

inline ll bigmod(ll x, ll pw){
    if(pw==0)return 1;
    x=mod(x);
    pw=mod(pw);
    ll ret=1;
    while(pw){
        if(pw&1)ret = mod(ret*x);
        x = mod(x*x);
        pw>>=1;
    }
    return ret;
}

int gSum(int a, ll r, ll n){
    if(n<0)return a;
    ll numerator = bigmod(r,n)-1;
    if(numerator<0)numerator+=MOD;
    ll denominator = bigmod(r-1,MOD-2);
    numerator = mod(numerator*denominator);
    return mod(1LL*a*numerator);
}

inline int trydel(segTree &F, segTree &R, int l, int r, int fl){
    int low=1,high=fl-l+1,mid;
    int cur=fl;
    while(low<=high){
        mid=(low+high)>>1;
        if(F.getHash(fl-mid+1,fl)==mod(1LL*gSum(s[fl-1],bases[0],mid)*P[n-mid])){
            cur=min(cur,fl-mid+1);
            low=mid+1;
        }
        else high=mid-1;
    }

    int hL = mod(1LL*F.query(l-1,cur-2)*P[n-r]);
    int hR = mod(1LL*F.query(cur,r-1)*P[n-r]);
    hL = mod(1LL*bases[0]*hL);

    int rL = mod(1LL*R.query(l-1,cur-2)*P[l-1]);
    int rR = mod(1LL*R.query(cur,r-1)*P[l-1]);
    rR = mod(1LL*bases[0]*rR);
    if(mod(1LL*hL + 1LL*hR) == mod(1LL*rR + 1LL*rL))return cur;
    return INT_MAX;
}

int main(){
    int T;
    P[0]=1;
    for(int j=1; j<=200003; j++)P[j] = mod(1LL*P[j-1]*bases[0]);


    scanf("%d",&T);
    for(int Case=1; Case<=T; Case++){
        scanf(" %s",&s);
        n=strlen(s);
        segTree F(n,0),R(n,1);
        for(int i=0; i<n; i++){
                F.update(i,s[i]);
                R.update(i,s[i]);
        }

        int q,qt=-1,l,r;
        char c;
        scanf("%d",&q);
        printf("Case %d:\n",Case);

        for(int Q=0; Q<q; Q++){
            //scanf("%d%d",&l,&r);
            //int G = mod(1LL*gSum('a',bases[0],r-l+1)*P[n-(r-l+1)]);
            //printf("hash: %d, gsum: %d\n",F.getHash(l,r),G);
            //printf("%d %d\n",F.getHash(l,r),R.getHash(l,r));
            scanf("%d",&qt);
            if(qt==1){
                scanf("%d%d",&l,&r);
                if(F.getHash(l,r)==R.getHash(l,r))printf("0\n");
                else if((r-l+1)==2)printf("%d\n",l);
                else{

                    int len=r-l+1;
                    int low=1,high=len/2,mid,fl=INT_MAX,fr=INT_MAX;
                    ///Find first mismatched character between prefix and suffix
                    while(low<=high){
                        mid=(low+high)>>1;
                        if(F.getHash(l,l+mid-1)==R.getHash(r-mid+1,r)){
                            low=mid+1;
                        }
                        else{
                            high=mid-1;
                            int ind=l+mid-1;
                            if(fl>ind){
                                fl=ind;
                                fr=r-mid+1;
                            }
                        }
                    }

                    if(fl==INT_MAX || fr==INT_MAX)printf("-1\n");
                    else{
                        ///Find leftmost occurence of mismatched character and try deleting it
                        int ans = min(trydel(F,R,l,r,fl), trydel(F,R,l,r,fr));
                        if(ans==INT_MAX)ans=-1;
                        printf("%d\n",ans);
                    }


                }
            }
            else if(qt==2){
                scanf("%d %c",&l,&c);
                l--;
                F.update(l,c);
                R.update(l,c);
                s[l]=c;
            }
        }
    }

return 0;
}
