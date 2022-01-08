#include<bits/stdc++.h>
using namespace std;

/*
    problem: Lightoj 1121, 15-Puzzle
    verdict: AC
*/

const int N=4;

    int goal[N][N]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};
    int mem[N*N][2];
    int mat[N][N];

    int count_inversions(){
        int cnt=N*N,inversions=0;
        for(int i=0; i<cnt-1; i++){
            for(int j=i+1; j<cnt; j++){
                if(mat[i/N][i%N]==0 || mat[j/N][j%N]==0)continue;
                if(mat[i/N][i%N]>mat[j/N][j%N])inversions++;
            }
        }
        return inversions;
    }

    inline void _swap(int &a, int &b){
        a^=b;
        b^=a;
        a^=b;
    }

    inline int _abs(int x){return x<0?x*(-1):x;}

    int manhattan(){
        int ret=0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(mat[i][j]==0)continue;
                ret+=_abs(i-mem[mat[i][j]][0]) + _abs(j-mem[mat[i][j]][1]);
            }
        }
        return ret;
    }

    int dx[4]={1,0,0,-1};
    int dy[4]={0,-1,1,0};
    char moves[5]={'D','L','R','U'};
    char opposite[200];
    char path[50];
    bool found;

    inline bool notSafe(int &xx, int &yy){
        return (xx>=N || xx<0) || (yy>=N || yy<0);
    }

    int dfs(int zx, int zy, int lvl, int bound, char prev){
        int mh=manhattan(),ret=10000;
        if(mh+lvl>bound || found)return mh+lvl;
        if(mh==0){
            found=1;
            path[lvl]='\0';
            printf("%s\n",path);
            return -1;
        }
        int i,newx,newy,val;
        for(int i=0; i<4; i++){
            newx=zx+dx[i];
            newy=zy+dy[i];
            if(notSafe(newx,newy) || found || opposite[moves[i]]==prev)continue;
            _swap(mat[zx][zy],mat[newx][newy]);
            path[lvl]=moves[i];
            val=dfs(newx,newy,lvl+1,bound,moves[i]);
            ret=min(ret,val);
            _swap(mat[zx][zy],mat[newx][newy]);
        }
        return ret;
    }

    bool IDA_star(){
        int zx,zy;
        for(int i=0; i<N; i++)for(int j=0; j<N; j++)
            if(mat[i][j]==0){
                zx=i;
                zy=j;
                break;
            }
        int in = count_inversions();
        if(!((in&1)==((3-zx)&1)))return 0;
        found=0;
        int mh=manhattan();
        for(int bound=mh,h; bound<=35;){
            h=dfs(zx,zy,0,bound,0);
            if(found)return 1;
            bound=h;
        }
        return 0;
    }


int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);

    opposite['U']='D';
    opposite['D']='U';
    opposite['R']='L';
    opposite['L']='R';

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            mem[goal[i][j]][0]=i;
            mem[goal[i][j]][1]=j;
        }
    }

    int t;
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){
        for(int i=0; i<N; i++)for(int j=0; j<N; j++)scanf("%d",&mat[i][j]);
        printf("Case %d: ",cas);
        if(!IDA_star())printf("This puzzle is not solvable.\n");
    }
return 0;
}
