#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

struct node{
    int data;
    node *left,*right;
    node(){}
    node(int data, node *left, node *right):data(data),left(left),right(right){}
}Tree[21*N];
int nodeCnt=0;
int arr[N],arr1[N];
int original[N];
unordered_map<int,int>mp;
int mpCnt=1;

node *newNode(int data=0, node *left=NULL, node *right=NULL){
    Tree[nodeCnt]=node(data,left,right);
    return &Tree[nodeCnt++];
}

void build(node *cur, int l, int r){
    if(l==r)return;
    cur->left=newNode();
    cur->right=newNode();
    int mid=(l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
}

node *update(node *cur, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(cur->data+val);
    node *tmp=newNode();
    int mid = (l+r)>>1;
    tmp->left=update(cur->left,l,mid,pos,val);
    tmp->right=update(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

inline int findKth(node *curL, node *curR, int l, int r, int k){
    int mid,val;
    while(l<r){
        mid = (l+r)>>1;
        val= curR->left->data - curL->left->data;
        if(val>=k){
            curL = curL->left;
            curR = curR->left;
            r=mid;
        }
        else{
            curL = curL->right;
            curR = curR->right;
            l=mid+1;
            k-=val;
        }
    }
    return l;
}

struct queryData{
    int qType,l,r,k; ///1 = Add k, 2 = remove last, 3 = print k'th in range[l,r]
    queryData(){}
    queryData(int qType, int l, int r, int k):qType(qType),l(l),r(r),k(k){}
};

int main(){
    int n,m;
    scanf("%d",&n);
    vector<int>tmp;
    mp.max_load_factor(0.25);
    mp.reserve(1<<12);
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
        arr1[i]=arr[i];
        tmp.push_back(arr[i]);
    }

    vector<queryData>queries;
    int backPtr=n-1;
    scanf("%d",&m);
    for(int i=0,qt,l,r,k; i<m; i++){
        scanf("%d",&qt);///1 = Add k, 2 = remove last, 3 = print k'th in range[l,r]
        if(qt==1){
            scanf("%d",&k);
            queries.emplace_back(1,-1,-1,k);
            arr1[++backPtr]=k;
            tmp.push_back(k);
        }
        else if(qt==2){
            queries.emplace_back(2,-1,-1,-1);
            backPtr--;
        }
        else {
            scanf("%d%d%d",&l,&r,&k);
            queries.emplace_back(3,l,r,k);
        }
    }

    sort(tmp.begin(),tmp.end());
    tmp.erase(unique(tmp.begin(),tmp.end()), tmp.end());
    for(int i:tmp){
        mp[i]=mpCnt;
        original[mpCnt]=i;
        mpCnt++;
    }

    for(int i=0; i<n; i++)arr[i]=mp[arr[i]];
    for(int i=0; i<m; i++){
        if(queries[i].qType==1){
            queries[i].k=mp[queries[i].k];
        }
    }

    vector<node*>roots({newNode()});
    build(roots.back(),1,mpCnt);

    for(int i=0; i<n; i++){
        roots.emplace_back(update(roots.back(),1,mpCnt,arr[i],1));
    }

    for(int i=0,l,r,k; i<m; i++){
        if(queries[i].qType==1){
            roots.emplace_back(update(roots.back(), 1, mpCnt, queries[i].k, 1));
        }
        else if(queries[i].qType==2){
            roots.pop_back();
        }
        else{
            l=queries[i].l;
            r=queries[i].r;
            k=queries[i].k;
            printf("%d\n",original[findKth(roots[l-1], roots[r], 1, mpCnt, (r-l+1)-k+1)]);
        }
    }
return 0;
}
