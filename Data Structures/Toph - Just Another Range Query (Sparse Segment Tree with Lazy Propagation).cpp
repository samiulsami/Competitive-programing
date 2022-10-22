#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=1e5+5;

struct node{
    ll data,lazy;
    node *left, *right;
    node(){
        data=lazy=0;
        left=NULL;
        right=NULL;
    }
    node(ll data, ll lazy, node *left=NULL, node *right=NULL):data(data),lazy(lazy),left(left),right(right){}
}Tree[40*N];
int nodeCnt=0;

inline ll calcInitialVal(int l, int r){
    l--;
    ll R = 1LL*(r*(r+1LL))>>1;
    ll L = 1LL*(l*(l+1LL))>>1;
    return R-L;
}

inline node *newNode(ll data, ll lazy, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data, lazy,left, right);
    return &Tree[nodeCnt++];
}

inline void expand(node *cur, int l, int r){
    int mid=(l+r)>>1;
    if(cur->left==NULL)cur->left = newNode(calcInitialVal(l,mid),0);
    if(cur->right==NULL)cur->right = newNode(calcInitialVal(mid+1,r),0);
}

inline void push_update(node *cur, int l, int r){
    if(cur->lazy!=0){
        cur->data = cur->data + 1LL*(r-l+1)*cur->lazy;
        if(l!=r){
            expand(cur,l,r);
            cur->left->lazy += cur->lazy;
            cur->right->lazy += cur->lazy;
        }
        cur->lazy=0;
    }
}

void update(node *cur, int l, int r, int posl, int posr, ll val){
    push_update(cur,l,r);
    if(l>r || l>posr || r<posl)return;
    else if(l>=posl && r<=posr){
        cur->lazy+=val;
        push_update(cur,l,r);
    }
    else{
        int mid = (l+r)>>1;
        expand(cur,l,r);
        update(cur->left, l, mid, posl, posr, val);
        update(cur->right, mid+1, r, posl, posr, val);
        cur->data = cur->left->data + cur->right->data;
    }
}

ll query(node *cur, int l, int r, int posl, int posr){
    push_update(cur,l,r);
    if(l>r || l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    expand(cur,l,r);
    return query(cur->left, l, mid, posl, posr) + query(cur->right, mid+1, r, posl, posr);
}

int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    node *root = newNode(calcInitialVal(1,n),0);

    int l,r,v,qt;

    while(q--){
        scanf("%d",&qt);
        if(qt==1){
            scanf("%d%d%d",&l,&r,&v);
            update(root,1,n,l,r,-v);
        }
        else{
            scanf("%d%d",&l,&r);
            printf("%lld\n",query(root,1,n,l,r));
        }
    }

return 0;
}
