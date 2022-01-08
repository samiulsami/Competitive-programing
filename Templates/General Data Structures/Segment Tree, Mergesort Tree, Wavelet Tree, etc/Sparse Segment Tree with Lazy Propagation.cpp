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

inline node *newNode(ll data, ll lazy, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data, lazy,left, right);
    return &Tree[nodeCnt++];
}

inline void expand(node *cur, int l, int r){
    if(cur->left==NULL)cur->left = newNode(0,0);
    if(cur->right==NULL)cur->right = newNode(0,0);
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

