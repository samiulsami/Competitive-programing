#include<bits/stdc++.h>
using namespace std;

/*
    problem: Lightoj 1139, 8-Puzzle
    verdict: AC
*/

const int N=3;
typedef unsigned long long ull;

struct node{
    int mat[N][N];
    int zx,zy;
    int lvl;
    int mh;
    int Hash;
    node(){}
    bool operator<(const node &nd)const{
        int f_nd=nd.mh+nd.lvl;
        int f = mh+lvl;
        if(f_nd==f)return nd.lvl<lvl;
        return f_nd<f;
    }
};

int cantor_arr[10];

int goal[N][N]={{1,2,3},{4,5,6},{7,8,0}};

void init(){
    cantor_arr[0]=1;
    for(int i=1; i<9; i++)cantor_arr[i]=i*cantor_arr[i-1];
}

int getHash(int (*mat)[N]){
    int ret=0,inversions,cnt=N*N;
    for(int i=0; i<cnt; i++){
        inversions=0;
        for(int j=i+1; j<cnt; j++){
            if(mat[i/3][i%3]>mat[j/3][j%3])inversions++;
        }
        ret+=cantor_arr[cnt-i-1]*inversions;
    }
    return ret;
}

int manhattan(int (*mat)[N]){
        int ret=0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(mat[i][j]==0)continue;
                ret+=abs(i-(mat[i][j]-1)/3) + abs(j-(mat[i][j]-1)%3);
            }
        }
            //cout<<"ret: "<<ret<<endl;
        return ret;
}

int count_inversions(int (*mat)[N]){
    int cnt=N*N,inversions=0;
    for(int i=0; i<cnt-1; i++){
        for(int j=i+1; j<cnt; j++){
            if(mat[i/3][i%3]==0 || mat[j/3][j%3]==0)continue;
            if(mat[i/3][i%3]>mat[j/3][j%3])inversions++;
        }
    }
    return inversions;
}

void printMat(int (*mat)[N]){
    for(int i=0; i<N; i++){
            for(int j=0; j<N; j++)cout<<mat[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

inline bool safe(int x, int y){
    return (x>=0 && x<N) && (y>=0 && y<N);
}

int A_star(int (*initial_mat)[N]){
    node root;
    root.lvl=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            root.mat[i][j]=initial_mat[i][j];
            if(root.mat[i][j]==0){
                root.zx=i;
                root.zy=j;
            }
        }
    }
    root.mh = manhattan(root.mat);
    root.Hash = getHash(root.mat);
    int goal_hash=getHash(goal);
    bool vis[400005]={0};
    vis[root.Hash]=1;

    priority_queue<node>pq;
    pq.push(root);

    int dx[5]={-1,1,0,0};
    int dy[5]={0,0,-1,1};

    while(!pq.empty()){
        root=pq.top();
        pq.pop();
        if(root.Hash==goal_hash)return root.lvl;
        //cout<<"ROOT: "<<endl;
        //printMat(root.mat);
        //cout<<"Moves: "<<endl;
        for(int i=0,zx,zy,newx,newy; i<4; i++){
            node top=root;
            zx=top.zx;
            zy=top.zy;
            newx=zx+dx[i];
            newy=zy+dy[i];

            if(!safe(newx,newy))continue;
            top.lvl++;
            swap(top.mat[zx][zy],top.mat[newx][newy]);
            top.zx=newx;
            top.zy=newy;
            top.Hash = getHash(top.mat);
            top.mh=manhattan(top.mat);
            //printMat(top.mat);
            if(top.Hash==goal_hash)return top.lvl;
            if(vis[top.Hash])continue;
            vis[top.Hash]=1;
            pq.push(top);
        }
       //cout<<"end moves-------------------------\n"<<endl;
    }
    return 42069;
}

int main(){
    //freopen("input1.txt","r",stdin);
   // freopen("output.txt","w",stdout);
    init();
    int mat[N][N];
    int t;
    cin>>t;
    for(int cas=1; cas<=t; cas++){
        for(int i=0; i<N; i++)for(int j=0; j<N; j++)cin>>mat[i][j];
        int inversions = count_inversions(mat);
        cout<<"Case "<<cas<<": ";
        if(N%2 && inversions%2)cout<<"impossible"<<endl;
        else cout<<A_star(mat)<<endl;
    }
return 0;
}
