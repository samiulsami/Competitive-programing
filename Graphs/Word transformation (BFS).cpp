#include<bits/stdc++.h>
using namespace std;

vector<string>dictionary;
map<string,vector<string> >graph;

int main(){
    //freopen("output.txt","w",stdout);
    int n,t;
    string dict,tmp,cur,goal;
    cin>>n;
    while(n--){
        dictionary.clear();
        graph.clear();
        while(cin>>dict && dict!="*")dictionary.push_back(dict);
        for(int i=0; i<(int)dictionary.size(); i++){
            for(int j=i+1; j<(int)dictionary.size(); j++){
                int counter=0;
                if(dictionary[i].length()!=dictionary[j].length())continue;
                for(int k=0; k<dictionary[i].length(); k++)counter+=(dictionary[i][k]!=dictionary[j][k]);
                if(counter==1){
                    graph[dictionary[i]].push_back(dictionary[j]);
                    graph[dictionary[j]].push_back(dictionary[i]);
                }
            }
        }
        cin.ignore();
        while(getline(cin,tmp)){
            if(tmp.empty())break;
            cur="";
            goal="";
            bool b=0;
            for(int i=0; i<tmp.size(); i++){
                if(tmp[i]==' '){
                    b=1;
                    continue;
                }
                if(b)goal+=tmp[i];
                else cur+=tmp[i];
            }
            queue<string>q;
            map<string,int>level;
            q.push(cur);
            level[cur]=0;
            int ans;
            while(!q.empty()){
                string top=q.front();
                if(top==goal){
                    ans=level[top];
                    break;
                }
                q.pop();
                for(int i=0; i<(int)graph[top].size(); i++){
                    if(level[graph[top][i]])continue;
                    level[graph[top][i]]=level[top]+1;
                    q.push(graph[top][i]);
                }
            }
            cout<<cur<<" "<<goal<<" "<<ans<<endl;
        }
        if(n)cout<<endl;
    }
return 0;
}
