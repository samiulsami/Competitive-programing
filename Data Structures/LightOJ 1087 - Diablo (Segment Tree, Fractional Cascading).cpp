#include<bits/stdc++.h>
using namespace std;
#define sf scanf
#define pf printf

const int N = 15e4+10;
int arr[N];

struct node{
    int data;
    node *left,*right;
    node(){
        left=right=this;
        data=0;
    }
}Tree[2*N];
int nodeCnt=0;

inline node *newNode(int data=0){
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r)cur->data=0;
    else{
        int mid = (l+r)>>1;
        cur->left = newNode();
        cur->right = newNode();
        build(cur->left,l,mid);
        build(cur->right,mid+1,r);
        cur->data = cur->left->data + cur->right->data;
    }
}

void update(node *cur, int l, int r, int pos, int val){
    if(pos>r || pos<l || l>r)return;
    if(l==pos && r==pos)cur->data=val;
    else{
        int mid = (l+r)>>1;
        if(pos<=mid)update(cur->left, l, mid, pos, val);
        else update(cur->right, mid+1, r, pos, val);
        cur->data = cur->left->data + cur->right->data;
    }
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl || l>r)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left, l, mid, posl, posr) + query(cur->right, mid+1, r, posl, posr);
}

int Search(node *cur, int l, int r, int q){
    if(l==r)return l;
    int mid = (l+r)>>1;
    int val=cur->left->data;
    if(val>=q)return Search(cur->left,l,mid,q);
    return Search(cur->right,mid+1,r,q-cur->left->data);
}

int main(){
    //freopen("output.txt","w",stdout);
    int T,q,n,m,low,high,mid,mn;
    char c;
    sf("%d",&T);

    for(int Case=1; Case<=T; Case++){
        nodeCnt=0;
        node *root = newNode();
        build(root,1,N);
        sf("%d%d",&n,&m);
        for(int i=1; i<=n; i++){
                sf("%d",&arr[i]);
                update(root,1,N,i,1);
        }

        pf("Case %d:\n",Case);

        for(int queries=0; queries<m; queries++){
            sf(" %c%d",&c,&q);

            if(c=='c'){
                if(query(root,1,N,1,N)<q){
                    pf("none\n");
                    continue;
                }
                low=1,high=N,mn=N;
                int mn = Search(root,1,N,q);


                pf("%d\n",arr[mn]);
                update(root,1,N,mn,0);
                arr[mn]=0;

            }
            else{
                update(root,1,N,n+1,1);
                arr[n+1]=q;
                n++;
            }

        }
    }
}
