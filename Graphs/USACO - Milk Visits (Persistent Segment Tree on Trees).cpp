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
}Tree[22*N];
int nodeCnt=0;

int cow[N];

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

int query(node *cur1, node *cur2, int l, int r, int posl, int posr){
    if(l>posr || r<posl)return 0;
    if(l>=posl && r<=posr)return cur1->data-cur2->data;
    int mid = (l+r)>>1;
    return query(cur1->left, cur2->left, l, mid, posl, posr) + query(cur1->right, cur2->right, mid+1, r, posl, posr);
}

node *roots[N];

vector<int>graph[N];

struct LCA{
    ///LCA with Range Minimum Query, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>discoveryTime,lvl,lgVal;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root=1):n(n),discoveryTime(n+1),lvl(n+1),lgVal(1+n<<1){
        lvl[root]=0;
        Time=0;
        for(int i=2,lim=n+n; i<=lim; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(1+n<<1));
        dfs(root,-1);

        for(int i=1; i<LOG; i++){
            for(int j=1; j+(1<<i)-1<=Time; j++){
                int left=sparseTable[i-1][j];
                int right=sparseTable[i-1][j+(1<<(i-1))];
                if(lvl[left]<lvl[right])sparseTable[i][j] = left;
                else sparseTable[i][j] = right;
            }
        }
    }

    void dfs(int u, int p){
        discoveryTime[u]=++Time;
        sparseTable[0][Time]=u;

        if(p==-1)roots[u]=update(roots[0],1,N,cow[u],1);
        else roots[u]=update(roots[p],1,N,cow[u],1);

        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                dfs(v,u);
                sparseTable[0][++Time]=u;
            }
    }

    inline int lca(int u, int v){
        u=discoveryTime[u];
        v=discoveryTime[v];
        if(u>v)swap(u,v);
        int logVal = lgVal[v-u+1];
        int x=sparseTable[logVal][u];
        int y=sparseTable[logVal][v-(1<<logVal)+1];
        if(lvl[x]<lvl[y])return x;
        return y;
    }
};

int main(){
    freopen("milkvisits.in","r",stdin);
    freopen("milkvisits.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    roots[0]=newNode();
    build(roots[0],1,N);

    for(int i=1; i<=n; i++)scanf("%d",&cow[i]);
    for(int i=1,u,v; i<n; i++){
        scanf("%d%d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    LCA lca(n,1);

    int x,y,z;
    vector<char>ans;

    while(m--){
        scanf("%d%d%d",&x,&y,&z);
        int L = lca.lca(x,y);
        if(cow[L]==z || query(roots[x], roots[L], 1, N, z, z)>0 || query(roots[y], roots[L], 1, N, z, z)>0)ans.push_back('1');
        else ans.push_back('0');
    }

    for(char c:ans)printf("%c",c);
return 0;
}
