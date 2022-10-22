#include<bits/stdc++.h>
using namespace std;

/*
    lightoj: 1026 Critical Links
    verdict: AC

*/

int discovery_time[10005];
int Time;
vector<pair<int,int> >ans;
vector<int>graph[10005];

int dfs(int u,int parent){
    int low=discovery_time[u]=++Time;
    for(int v : graph[u]){
        if(v==parent)continue;
        if(discovery_time[v]){
            low=min(low,discovery_time[v]);
        }
        else{
            int subtree_min=dfs(v,u);
            if(discovery_time[u]<subtree_min){
                if(u<v)ans.push_back(make_pair(u,v));
                else ans.push_back(make_pair(v,u));
            }
            low=min(low,subtree_min);
        }
    }
    return low;
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    char s[20];
    int powers[10]={0};
    powers[0]=1;
    for(int i=1; i<8; i++)powers[i]=powers[i-1]*10;

    for(int cas=1; cas<=t; cas++){
        scanf("%d",&n);

        ans.clear();
        Time=0;
        for(int i=0; i<n; i++){
            discovery_time[i]=0;
            graph[i].clear();
        }

        for(int i=0,u,m,len; i<n; i++){
            scanf("%d %s",&u,&s);
            len = strlen(s);
            m=0;
            for(int j=1; j<len-1; j++)
                m+=(powers[len-2-j]*(int)(s[j]-48));

            for(int j=0,v; j<m; j++){
                scanf("%d",&v);
                graph[u].push_back(v);
            }
        }

        for(int i=0; i<n; i++){
            if(!discovery_time[i])
                dfs(i,i);
        }

        printf("Case %d:\n%d critical links\n",cas,(int)ans.size());
        sort(ans.begin(),ans.end());
        for(int i=0; i<(int)ans.size(); i++){
            printf("%d - %d\n",ans[i].first,ans[i].second);
        }
    }
return 0;
}
