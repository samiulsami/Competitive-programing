#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef long long ll;

seed_seq seq{
(uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
(uint64_t) __builtin_ia32_rdtsc(),
(uint64_t) (uintptr_t) make_unique<char>().get()};
mt19937 rng(seq);

inline int rand(int l, int r){
    uniform_int_distribution<int> rangeRNG(l,r);
    return rangeRNG(rng);
}

const int N=1e5+5;
const int MOD=(1LL<<31)-1;
const int _hashCnt=1;
const int bases[2] = {rand(11887,1<<21),rand(15661,1<<22)};
int P[_hashCnt][N];
char s[N];

inline int mod(ll x) {
    x+=MOD;
    x=(x>>31)+(x&MOD);
    return int((x>>31)+(x&MOD));
}

struct data{///0-indexed
        int h[_hashCnt],r[_hashCnt];
        int cnt;
        data(){
            cnt=0;
            for(int i=0; i<_hashCnt; i++)h[i]=r[i]=0;
        }
        void update(int c, int cnt){
            for(int i=0; i<_hashCnt; i++)
                h[i]=r[i]=c;
            this->cnt=cnt;
        }
        data operator+(const data &nd)const{
            data ret;
            ret.cnt=cnt+nd.cnt;
            for(int i=0; i<_hashCnt; i++){
                ret.h[i] = mod(1LL*h[i] + mod(1LL*P[i][cnt]*nd.h[i]));
                ret.r[i] = mod(1LL*nd.r[i] + mod(1LL*P[i][nd.cnt]*r[i]));
            }
            return ret;
        }
}Tree[4*N];

void update(int node, int l, int r, int pos, int c, int val){///1-indexed
    if(l>r || l>pos || r<pos)return;
    if(l==pos && r==pos)Tree[node].update(c,val);
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(node*2, l, mid, pos, c, val);
        else update(node*2 + 1 , mid+1, r, pos, c, val);
        Tree[node] = Tree[node*2] + Tree[node*2+1];
    }
}

data query(int node, int l, int r, int posl, int posr){///1-indexed
    if(l>r || r<posl || l>posr)return data();
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    return query(node*2, l, mid, posl, posr) + query(node*2+1, mid+1, r, posl, posr);
}

int findKth(int node, int l, int r, int k){
    if(l==r)return l;
    int mid = (l+r)>>1, val=Tree[node*2].cnt;
    if(val>=k)return findKth(node*2, l, mid, k);
    return findKth(node*2+1, mid+1, r, k-val);
}


bool isPalindrome(int l, int r, int n){///1-indexed
    data H=query(1,1,n,l,r);
    for(int i=0; i<_hashCnt; i++){
        if(H.h[i]!=H.r[i])return 0;
    }
    return 1;
}

int main(){
    scanf("%s",&s);
    int n=strlen(s);
    for(int i=0; i<_hashCnt; i++){
        P[i][0]=1;
        for(int j=1; j<=n+1; j++)P[i][j] = mod(1LL*P[i][j-1]*bases[i]);
    }

    for(int i=0; i<n; i++)
        update(1,1,n,i+1,s[i],1);

    int q,l,r;
    char c;
    scanf("%d",&q);
    while(q--){
        scanf(" %c",&c);
        if(c=='C'){
            scanf("%d%d",&l,&r);
            l=findKth(1,1,n,l);
            r=findKth(1,1,n,r);
            if(isPalindrome(l,r,n))printf("Yes!\n");
            else printf("No!\n");
        }
        else if(c=='D'){
            scanf("%d",&l);
            l=findKth(1,1,n,l);
            update(1,1,n,l,0,0);
        }
        else if(c=='U'){
            scanf("%d %c",&l,&c);
            l=findKth(1,1,n,l);
            update(1,1,n,l,c,1);
        }
    }


return 0;
}
