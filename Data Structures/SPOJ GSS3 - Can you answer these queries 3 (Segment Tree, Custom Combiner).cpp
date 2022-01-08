#include<bits/stdc++.h>
using namespace std;

const int N = 5e4+5;

struct data{
    int pref,suff,total,best;
    data(){}
    data(int pref, int suff, int total, int best):pref(pref),suff(suff),total(total),best(best){}
    data(int x){pref=suff=total=best=x;}
};

inline data Combine(data L, data R){
    data ret;
    ret.pref = max(L.pref, L.total + R.pref);
    ret.suff = max(R.suff, R.total + L.suff);
    ret.best = max({L.best, R.best, L.suff+R.pref});
    ret.total = L.total + R.total;
    return ret;
}

data Tree[4*N];
int arr[N];

void build(int node, int l, int r){
    if(l==r)Tree[node]=data(arr[l-1]);
    else{
        int mid = (l+r)>>1;
        build(node*2, l, mid);
        build(node*2+1, mid+1, r);
        Tree[node] = Combine(Tree[node*2], Tree[node*2+1]);
    }
}

data query(int node, int l, int r, int posl, int posr){
    if(l==posl && r==posr)return Tree[node];
    int mid = (l+r)>>1;
    if(posl>mid)return query(node*2+1, mid+1, r, posl, posr);
    else if(posr<=mid)return query(node*2, l, mid, posl, posr);
    else return Combine(query(node*2, l, mid, posl, mid), query(node*2+1, mid+1, r, mid+1, posr));
}

void update(int node, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return;
    if(l==pos && r==pos)Tree[node]=val;
    else{
            int mid = (l+r)>>1;
        if(pos<=mid)update(node*2, l, mid, pos, val);
        else update(node*2+1, mid+1, r, pos, val);
        Tree[node] = Combine(Tree[node*2], Tree[node*2+1]);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)scanf("%d",&arr[i]);
    build(1,1,n);
    int m;
    scanf("%d",&m);
    int l,r,x;
    while(m--){
        scanf("%d%d%d",&x,&l,&r);
        if(x==1)printf("%d\n",query(1,1,n,l,r).best);
        else update(1,1,n,l,r);
    }

return 0;
}
