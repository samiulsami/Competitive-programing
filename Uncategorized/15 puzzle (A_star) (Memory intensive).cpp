#include<bits/stdc++.h>
using namespace std;

/*
    problem: Lightoj 1121, 15-Puzzle
    verdict: MLE
*/

const int N=4;
typedef unsigned long long ull;

struct node{
    int mat[N][N];
    int zx,zy;
    int lvl,mh,f;
    char path[36];
    ull Hash;
    bool operator<(const node &nd)const{
        int cmp=strcmp(nd.path,path);
        if(nd.f==f){
            if(cmp==0)return nd.lvl<lvl;
            return cmp<0;
        }
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

    int goal[N][N]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

    /*int printMat(int (*mat)[N]){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++)cout<<mat[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }*/

    int count_inversions(int (*mat)[N]){
        int cnt=N*N,inversions=0;
        for(int i=0; i<cnt-1; i++){
            for(int j=i+1; j<cnt; j++){
                if(mat[i/N][i%N]==0 || mat[j/N][j%N]==0)continue;
                if(mat[i/N][i%N]>mat[j/N][j%N])inversions++;
            }
        }
        return inversions;
    }

    int manhattan(int (*mat)[N]){
        int ret=0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(mat[i][j]==0)continue;
                ret+=abs(i-(mat[i][j]-1)/N) + abs(j-(mat[i][j]-1)%N);
            }
        }
        return ret;
    }

    int dx[4]={1,0,0,-1};
    int dy[4]={0,-1,1,0};
    char moves[4]={'D','L','R','U'};

    void A_star(int (*initial_matrix)[N]){
        priority_queue<node>q;
        map<ull,bool>vis;
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
        if(!(((root.zx+1)&1) != ((count_inversions(root.mat))&1))){
                printf("This puzzle is not solvable.\n");
                return;
        }
        root.Hash=hash_functions::getHash(root.mat);
        root.mh=manhattan(root.mat);
        root.f=root.mh+root.lvl;
        vis[root.Hash]=1;
        root.path[0]='\0';
        q.push(root);
        while(!q.empty()){
            root=q.top();
            q.pop();
           /* cout<<"ROOT: "<<endl;
            printMat(root.mat);
            cout<<"Moves: "<<endl;*/
            if(root.lvl>=35){
                printf("This puzzle is not solvable.\n");
                return;
            }
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
                top.lvl++;
                //printMat(top.mat);
                if(top.lvl>35){
                    printf("This puzzle is not solvable.\n");
                    return;
                }
                top.path[top.lvl-1]=moves[i];
                if(top.Hash==goal_hash){
                    top.path[top.lvl]='\0';
                    printf("%s\n",top.path);
                    return;
                }
                if(vis[top.Hash])continue;
                vis[top.Hash]=1;
                top.mh=manhattan(top.mat);
                top.f=top.mh+top.lvl;
                q.push(top);
            }
            //cout<<"end moves-------------------------\n"<<endl;
        }
        printf("This puzzle is not solvable.\n");
        return;
    }
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    hash_functions::init_table();
    int mat[N][N];
    int t;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        for(int i=0; i<N; i++)for(int j=0; j<N; j++)scanf("%d",&mat[i][j]);
        printf("Case %d: ",cas);
        search_functions::A_star(mat);
    }
return 0;
}

