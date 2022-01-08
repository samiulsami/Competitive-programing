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
    if(l==pos && r==pos)Tree[node].update(c,val);
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(node*2, l, mid, pos, c, val);
        else update(node*2 + 1 , mid+1, r, pos, c, val);
        Tree[node] = Tree[node*2] + Tree[node*2+1];
    }
}

data query(int node, int l, int r, int posl, int posr){///1-indexed
    if(l>=posl && r<=posr)return Tree[node];
    int mid = (l+r)>>1;
    if(posl>mid)return query(node*2+1, mid+1, r, posl, posr);
    if(posr<=mid)return query(node*2, l, mid, posl, posr);
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
