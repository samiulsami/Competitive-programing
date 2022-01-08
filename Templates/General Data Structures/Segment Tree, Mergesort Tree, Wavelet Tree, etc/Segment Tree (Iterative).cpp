/**
    Based on https://codeforces.com/blog/entry/18051
*/

const int MAX = 1e5+5;
int n;
int Tree[2*MAX];

void build(){
    for(int i=n-1; i>0; i--)Tree[i]=Tree[i<<1]+Tree[i<<1|1];
}

void point_update(int ind, int val){
    ind+=n;
    Tree[ind]=val;
    for(;ind>1; ind>>=1)Tree[ind>>1] = Tree[ind]+Tree[ind^1];
}

int range_query(int l, int r){ ///[l,r]
    l+=n;
    r+=n+1;
    int ret=0;
    for(;l<r; l>>=1,r>>=1){
        if(l&1)ret+=Tree[l++];
        if(r&1)ret+=Tree[--r];
    }
    return ret;
}

///------------------------------------------

void range_update(int l, int r, int val){ ///[l,r]
    l+=n;
    r+=n+1;
    for(;l<r; l>>=1,r>>=1){
        if(l&1)Tree[l++]+=val;
        if(r&1)Tree[--r]+=val;
    }
}

int point_query(int ind){
    int ret=0;
    for(ind+=n; ind>0; ind>>=1)ret+=Tree[ind];
    return ret;
}

