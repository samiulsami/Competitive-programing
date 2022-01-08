#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+5;

struct node{
    int data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[30*N];
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
    if(l==pos && r==pos)return newNode(cur->data+val);
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

int dTime[N],eTime[N],euler[N];
int lvl[N];
int Time=0;

vector<int>graph[N];

void dfs(int u, int p){
    dTime[u]=++Time;
    euler[Time]=u;
    for(int v:graph[u])
        if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
        }
    eTime[u]=Time;
}

int main(){
    int n;
    scanf("%d",&n);

    for(int i=2,u; i<=n; i++){
        scanf("%d",&u);
        graph[i].push_back(u);
        graph[u].push_back(i);
    }

    lvl[1]=0;
    dfs(1,1);

    vector<node*>roots{newNode()};
    build(roots.back(),0,n);
    for(int i=1; i<=Time; i++){
        roots.emplace_back(update(roots.back(),0,n,lvl[euler[i]],1));
    }

    int q;
    scanf("%d",&q);
    while(q--){
        int x,y;
        scanf("%d%d",&x,&y);
        int l=dTime[x],r=eTime[x];
        printf("%d\n",query(roots[r],0,n,y,y) - query(roots[l-1],0,n,y,y));
    }

return 0;
}
