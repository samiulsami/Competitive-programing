#include<bits/stdc++.h>

using namespace std;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define all(x) x.begin(),x.end()

const int N = 1e5+5;

vector<int>graph[N];
int weight[N];
int originalWeight[N];

struct node{
    int data;
    node *left,*right;
    node(){
        data=0;
        left=right=this;
    }
    node(int data, node *left=NULL, node *right=NULL):data(data),left(left),right(right){}
}Tree[21*N];
int nodeCnt=0;
int lim;
node *roots[N];

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

int query(node *u, node *v, node *L, node *Lpar, int l, int r, int k){
    if(l==r)return l;
    int cnt = u->left->data + v->left->data - L->left->data;
    if(Lpar!=NULL)cnt-=Lpar->left->data;
    int mid = (l+r)>>1;
    if(cnt>=k)return query(u->left, v->left, L->left, (Lpar==NULL)?NULL:Lpar->left, l, mid, k);
    return query(u->right, v->right, L->right, (Lpar==NULL)?NULL:Lpar->right, mid+1, r, k-cnt);
}



struct LCA{
    ///LCA with Sparse Table, O(nlogn) preprocessing, O(1) per query
    ///******* EVERYTHING IS 1-INDEXED ********
    vector<int>euler,discoveryTime,lvl,lgVal,parent;
    vector<vector<int > >sparseTable;
    int LOG;
    int n,Time;

    LCA(int n, int root=1):n(n),euler(n+n+1),discoveryTime(n+1),parent(n+2),lvl(n+1),lgVal(n+n+1){
        lvl[root]=0;
        Time=0;
        dfs(root,0);
        parent[root]=-1;
        for(int i=2; i<=Time; i++)lgVal[i]=lgVal[(i>>1)]+1;
        LOG = lgVal[n]+2;
        sparseTable.resize(LOG, vector<int>(Time+1));

        for(int i=1; i<=Time; i++)sparseTable[0][i]=euler[i];
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
        euler[Time]=u;
        roots[u] = update(roots[p],1,lim,weight[u],1);
        for(int v:graph[u])
            if(v!=p){
                lvl[v]=lvl[u]+1;
                parent[v]=u;
                dfs(v,u);
                euler[++Time]=u;
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

inline void Solve(int Case){
    int n,m;
    sii(n,m);

    vector<int>tmp;
    for(int i=1; i<=n; i++){
        si(weight[i]);
        tmp.push_back(weight[i]);
    }

    map<int,int>mp;
    sort(all(tmp));
    tmp.erase(unique(all(tmp)),tmp.end());

    lim=0;
    for(int i:tmp){
            mp[i]=++lim;
            originalWeight[lim]=i;
    }
    for(int i=1; i<=n; i++)weight[i]=mp[weight[i]];

    for(int i=2,u,v; i<=n; i++){
        sii(u,v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    roots[0] = newNode();
    build(roots[0],1,lim);
    LCA lca(n,1);

    int u,v,k;

    while(m--){
        siii(u,v,k);
        int L = lca.lca(u,v);
        node *uu = roots[u];
        node *vv = roots[v];
        node *LL = roots[L];
        node *Lpar = NULL;
        if(lca.parent[L]!=-1)Lpar = roots[lca.parent[L]];
        pf("%d\n",originalWeight[query(uu,vv,LL,Lpar,1,lim,k)]);
    }
}


int main(){

        Solve(0);


return 0;
}
