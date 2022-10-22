#include<bits/stdc++.h>
/*
    problem: LightOJ 1003 - Drunk
    verdict: AC
*/
using namespace std;
typedef long long ll;

#define xx first
#define yy second
#define sf scanf
#define pf printf
#define dbug(x) cout<<"dbug: "<<x<<endl
const int MAX = 1e4+5;
map<string,int>mp;
vector<int>graph[MAX];
int inDegree[MAX];

void init(int m){
    for(int i=0; i<=m+1; i++){
           graph[i].clear();
           inDegree[i]=0;
    }
    mp.clear();
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T,m;
    cin>>T;
    string u,v;
    for(int cas=1; cas<=T; cas++){
        cin>>m;
        vector<pair<int,int> >edges;
        int cnt=0;

        for(int i=0,a,b; i<m; i++){
            cin>>u>>v;
            if(!mp.count(u))mp[u]=++cnt;
            if(!mp.count(v))mp[v]=++cnt;
            a=mp[u];
            b=mp[v];
            edges.push_back({a,b});
        }

        init(cnt);

        for(auto edge:edges){
            graph[edge.xx].push_back(edge.yy);
            inDegree[edge.yy]++;
        }

        int ans=0;
        queue<int>q;

        for(int i=1; i<=cnt; i++)
            if(inDegree[i]==0)q.push(i);

        while(!q.empty()){
            int u=q.front();
            q.pop();
            ans++;

            for(int v:graph[u]){
                if(--inDegree[v]==0)q.push(v);
            }
        }

        cout<<"Case "<<cas<<": ";
        if(ans==cnt)cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }



return 0;
}
