#include<bits/stdc++.h>
using namespace std;

int arr[int(1e5)];

/**************************** EVERYTHING IS 1-INDEXED*********************************/

struct node{
    int data,lazy;
    node *left,*right;
    node(int val=0, int lazy=0, node* left=NULL, node *right=NULL):lazy(lazy),data(val),left(left),right(right){}
};
const int N = 1e5+5;
int nodeCnt=0;
vector<node>Tree;
inline node *newNode(int data=0, int lazy=0, node *left=NULL, node *right=NULL){
    Tree.emplace_back(node());
    node *ret = &Tree[nodeCnt++];
    ret->data=data;
    ret->left=left;
    ret->right=right;
    ret->lazy=lazy;
    return ret;
}

void build(node *cur, int l, int r){
    if(l==r){
        cur->data=arr[l];
        return;
    }
    cur->left = newNode();
    cur->right = newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
    cur->data = cur->left->data + cur->right->data;
}
inline void push_update_clone(node *cur, int l, int r){
    if(cur->lazy!=0){
        cur->data += (r-l+1)*(cur->lazy);
        if(l!=r){
            cur->left = newNode(cur->left->data, cur->left->lazy+cur->lazy, cur->left->left, cur->left->right);
            cur->right = newNode(cur->right->data, cur->right->lazy+cur->lazy, cur->right->left, cur->right->right);
        }
        cur->lazy=0;
    }
}
node *cloneAndRangeUpdate(node *cur, int l, int r, int posl, int posr, int val){
    push_update_clone(cur,l,r);
    if(l>posr || r<posl)return cur;
    if(l>=posl && r<=posr){
        node *tmp = newNode(cur->data);
        tmp->data += (r-l+1)*(val);
        if(l!=r){
            int mid = (l+r)>>1;
            tmp->left = newNode(cur->left->data, cur->left->lazy+val, cur->left->left, cur->left->right);
            tmp->right = newNode(cur->right->data, cur->right->lazy+val, cur->right->left, cur->right->right);
        }
        return tmp;
    }
    node *tmp = newNode();
    int mid = (l+r)>>1;
    tmp->left = cloneAndRangeUpdate(cur->left,l,mid,posl,posr,val);
    tmp->right = cloneAndRangeUpdate(cur->right,mid+1,r,posl,posr,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}
int query(node *cur, int l, int r, int posl, int posr){
    push_update_clone(cur,l,r);
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left, l,mid,posl,posr) + query(cur->right, mid+1,r,posl,posr);
}
