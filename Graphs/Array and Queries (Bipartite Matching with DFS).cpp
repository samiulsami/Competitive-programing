#include<bits/stdc++.h>
/*
    Problem: Codeforces round 284 C (div. 1)
    verdict: AC
*/

using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define sf scanf
#define pf printf
#define dbug(x) cout<<"dbug: "<<x<<endl

const int MAX=8005;
int n,offset=3500,cnt=0;
int arr[105];
bool vis[MAX];
vector<int>graph[MAX];
vector<pair<int,int> >factors[105];
int matchR[MAX];

void factorize(int u){
    int uVal=arr[u];
    int sqt=sqrt(uVal)+5;
    for(int i=2; i*i<=sqt; i++){
        if(uVal%i==0){
            while(uVal%i==0){
                uVal/=i;
                factors[u].push_back({i,cnt++});
            }
        }
    }

    if(uVal>1)factors[u].push_back({uVal,cnt++});
}

bool match(int lft){
    if(vis[lft])return 0;
    vis[lft]=1;

    for(int r:graph[lft]){
        if(matchR[r]==-1){
            matchR[r]=lft;
            return 1;
        }
    }

    for(int r:graph[lft]){
        if(match(matchR[r])){
            matchR[r]=lft;
            return 1;
        }
    }

    return 0;
}

int bpm(){
    int ans=0;
    for(int i=0; i<=cnt; i++){
         if(graph[i].size()==0)continue;
         memset(vis,0,sizeof(vis));
         if(match(i))ans++;
    }
    return ans;
}

void addEdge(int u, int v){
    for(auto uf:factors[u]){
        for(auto vf:factors[v]){
            if(uf.xx==vf.xx){
                graph[uf.yy].push_back(vf.yy);
            }
            else if(vf.xx>uf.xx)break;
        }
    }
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int m;
    cin>>n>>m;
    for(int i=0; i<n; i++){
            cin>>arr[i];
            factorize(i);
    }

    for(int i=0,u,v; i<m; i++){
        cin>>u>>v;
        if(u&1)swap(u,v);
        u--,v--;
        addEdge(u,v);
    }

    memset(matchR,-1,sizeof(matchR));
    cout<<bpm();
return 0;
}
