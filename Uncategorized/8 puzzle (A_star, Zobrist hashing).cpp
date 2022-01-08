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
    int f;
    ull Hash;
    bool operator<(const node &nd)const{
        if(nd.f==f)return nd.lvl<lvl;
        return nd.f<f;
    }
    void make_move(int x,int y){
        swap(mat[zx][zy],mat[x][y]);
        zx=x;
        zy=y;
    }
};

namespace hash_functions{

    ull zobristTable[N][N][N*N]={0};
    mt19937 mt(123456);

    ull randInt(){
        uniform_int_distribution<ull>rnd(0,UINT_MAX);
        return rnd(mt);
    }

    void init_table(){
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                for(int k=1; k<N*N; k++)
                    zobristTable[i][j][k]=randInt();
    }

    ull getHash(int (*mat)[N]){
        ull h=0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                h^=zobristTable[i][j][mat[i][j]];
            }
        }
        return h;
    }

}

namespace search_functions{

    int goal[N][N]={{1,2,3},{4,5,6},{7,8,0}};

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

    int manhattan(int (*mat)[N]){
        int ret=0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(mat[i][j]==0)continue;
                ret+=abs(i-(mat[i][j]-1)/3) + abs(j-(mat[i][j]-1)%3);
            }
        }
        return ret;
    }

    /*int printMat(int (*mat)[N]){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++)cout<<mat[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }*/

    int dx[4]={1,0,-1,0};
    int dy[4]={0,1,0,-1};

    int A_star(int (*initial_matrix)[N]){
        priority_queue<node>pq;
        map<ull,int>vis;
        node root;
        root.lvl=0;
        ull goal_hash = hash_functions::getHash(goal);
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                root.mat[i][j]=initial_matrix[i][j];
                if(root.mat[i][j]==0){
                    root.zx=i;
                    root.zy=j;
                }
            }
        }
        root.Hash=hash_functions::getHash(root.mat);
        root.mh=manhattan(root.mat);
        root.f=root.mh+root.lvl;
        vis[root.Hash]=1;
        if(root.Hash==goal_hash)return 0;
        pq.push(root);
        while(!pq.empty()){
            root=pq.top();
            pq.pop();
           // cout<<"ROOT: "<<endl;
           // printMat(root.mat);
            //cout<<"Moves: "<<endl;
            for(int i=0,zx,zy,newx,newy; i<4; i++){
                node top=root;
                zx=top.zx;
                zy=top.zy;
                newx=zx+dx[i];
                newy=zy+dy[i];
                if(newx<0 || newx>=N || newy<0 || newy>=N)continue;
                top.Hash ^= hash_functions::zobristTable[zx][zy][top.mat[newx][newy]];
                top.Hash ^= hash_functions::zobristTable[newx][newy][top.mat[newx][newy]];
                top.make_move(newx,newy);
                top.mh=manhattan(top.mat);
                top.lvl++;
                top.f=top.mh+top.lvl;
               // printMat(top.mat);
                if(top.Hash==goal_hash)return top.lvl;
                if(vis[top.Hash])continue;
                vis[top.Hash]=1;
                pq.push(top);
            }
            //cout<<"end moves-------------------------\n"<<endl;
        }
        return 123456;
    }
}

int main(){
    //freopen("input1.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    hash_functions::init_table();
    int mat[N][N];
    int t;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        for(int i=0; i<N; i++)for(int j=0; j<N; j++)scanf("%d",&mat[i][j]);
        int inversions = search_functions::count_inversions(mat);
        printf("Case %d: ",cas);
        if(N%2 && inversions%2)printf("impossible\n");
        else printf("%d\n",search_functions::A_star(mat));
    }
return 0;
}
