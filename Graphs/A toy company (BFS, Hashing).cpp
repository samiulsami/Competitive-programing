#include<bits/stdc++.h>
using namespace std;

/*
    lightoj problem: 1039
    verdict: AC
*/

struct node{
    char str[4];
    int lvl;
};

int Hash(char *str){
    int ret=0;
    for(int i=0; str[i]; i++)ret+=str[i]+(31*ret);
    return ret;
}

inline void change_str(char *str, int index, int val){
    str[index]+=val;
    if(str[index]>'z')str[index]='a';
    else if(str[index]<'a')str[index]='z';
}

bool valid(char *str, set<char> (*f)[3], int n){
    for(int i=0; i<n; i++){
        bool invalid=1;
        for(int j=0; j<3; j++)
            if(f[i][j].find(str[j])==f[i][j].end())invalid=0;

        if(invalid)return 0;
    }
    return 1;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n;
    char start[4],goal[4],s[50];
    scanf("%d",&t);
    for(int cas=1; cas<=t; cas++){

        scanf("%s%s%d",&start,&goal,&n);

        set<char>forbidden[51][3];
        for(int i=0; i<n; i++)
            for(int k=0; k<3; k++){
                scanf("%s",&s);
                for(int j=0; s[j]; j++)
                    forbidden[i][k].insert(s[j]);
            }

        bool vis[128955]={0};
        bool found=0;
        int ans=-1;
        queue<node>q;
        node root;
        for(int i=0; start[i]; i++)root.str[i]=start[i];
        root.str[3]='\0';
        root.lvl=0;
        vis[Hash(root.str)]=1;

        int goalHash=Hash(goal);
        if(!(valid(start,forbidden,n) && valid(goal,forbidden,n))){
            ans=-1;
            found=1;
        }
        else{
            if(goalHash==Hash(start)){
                ans=0;
                found=1;
            }
            else q.push(root);
        }

        while(!(q.empty() || found)){
            node top=q.front();
            q.pop();
            top.lvl++;
            for(int i=0; i<3; i++){
                for(int val=1; val>=-1; val-=2){
                    change_str(top.str,i,val);
                    int topHash=Hash(top.str);
                    if(topHash==goalHash){
                        found=1;
                        ans=top.lvl;
                        break;
                    }
                    else if(!vis[topHash] && valid(top.str,forbidden,n)){//validity check not mandatory here
                        vis[topHash]=1;
                        q.push(top);
                    }
                    change_str(top.str,i,-val);
                }
            }
        }
        printf("Case %d: %d\n",cas,ans);
    }

return 0;
}
