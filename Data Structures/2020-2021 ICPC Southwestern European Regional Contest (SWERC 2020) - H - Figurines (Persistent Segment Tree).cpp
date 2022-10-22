#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;

struct node{
    int data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[42*N];
int nodeCnt=0;

inline node *newNode(int data=0, node *left=NULL, node *right=NULL){
    Tree[nodeCnt] = node(data,left,right);
    return &Tree[nodeCnt++];
}

void build(node *cur, int l, int r){
    if(l==r)return;
    cur->left=newNode();
    cur->right=newNode();
    int mid = (l+r)>>1;
    build(cur->left,l,mid);
    build(cur->right,mid+1,r);
}

node *update(node *cur, int l, int r, int pos, int val){
    if(l>r || l>pos || r<pos)return cur;
    if(l==pos && r==pos)return newNode(val);
    int mid = (l+r)>>1;
    node *tmp = newNode();
    tmp->left = update(cur->left,l,mid,pos,val);
    tmp->right = update(cur->right,mid+1,r,pos,val);
    tmp->data = tmp->left->data + tmp->right->data;
    return tmp;
}

int query(node *cur, int l, int r, int posl, int posr){
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur->data;
    int mid = (l+r)>>1;
    return query(cur->left, l, mid, posl, posr) + query(cur->right, mid+1, r, posl, posr);
}


int main(){
    int n;
    scanf("%d",&n);

    vector<node*>roots{newNode()};
    int lim = n+5;
    build(roots.back(),0,lim);

    char x,y;
    int a,b;
    getchar();
    for(int i=1; i<=n; i++){

        node *tmp=roots.back();

        while((x=getchar())!='\n'){
            if(x==' ')continue;
            scanf("%d",&a);
            if(x=='+')tmp=update(tmp,0,lim,a,1);
            else tmp=update(tmp,0,lim,a,0);

            //printf("%d\n",a);
        }
        //printf("here\n");

        roots.push_back(tmp);
    }

    vector<int>days(n);
    for(int i=0; i<n; i++){
        scanf("%d",&days[i]);
    }

    int ans=0;
    for(int i=0; i<n; i++){
        int day=days[i];
        int y = query(roots[day],0,lim,ans,n-1);
        //printf("y %d\n",y);
        int val = (ans+y)%n;
        ans = val%n;
    }

    printf("%d\n",ans%n);

return 0;
}
