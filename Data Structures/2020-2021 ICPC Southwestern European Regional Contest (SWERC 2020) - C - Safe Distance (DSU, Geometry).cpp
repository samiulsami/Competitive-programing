#include<bits/stdc++.h>
using namespace std;

typedef pair<double,double> pd;

struct data{
    int id;
    double leftmost,rightmost,downmost,upmost;
    data(){}
    data(int i, pd x, double radius){
        id=i;
        leftmost = x.first-radius;
        rightmost = x.first+radius;
        downmost = x.second-radius;
        upmost = x.second+radius;
    }
    void Merge(data &d){
        if(d.leftmost<leftmost)leftmost=d.leftmost;
        if(d.rightmost>rightmost)rightmost=d.rightmost;
        if(d.downmost<downmost)downmost=d.downmost;
        if(d.upmost>upmost)upmost=d.upmost;
    }
}parent[1003];

int Find(int i){
    if(parent[i].id==i)return i;
    int tmp = Find(parent[i].id);
    parent[i].id=tmp;
    return tmp;
}

double dist(pd &a, pd &b){
    double x = a.first-b.first;
    double y = a.second-b.second;
    return sqrt((x*x)+(y*y));
}

int main(){
    int n;
    double X,Y;
    scanf("%lf%lf%d",&X,&Y,&n);

    vector<pd>people(n);
    for(int i=0; i<n; i++){
        scanf("%lf%lf",&people[i].first, &people[i].second);
        //swap(people[i].first,people[i].second);
    }

    double low=0,high=2e6,mid,ans=0;

    for(int sdkljf=0; sdkljf<=52; sdkljf++){
        mid = (low+high)/double(2);

        //printf("radius: %0.5lf\n",mid);
        bool vis[n+1];
        for(int i=0; i<n; i++){
            parent[i] = data(i,people[i],mid);
            vis[i]=0;
        }

        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if(dist(people[i],people[j])<(mid+mid)){
                    int x = Find(i);
                    int y = Find(j);
                    if(x==y)continue;

                    parent[x].Merge(parent[y]);
                    parent[y].id = parent[x].id;
                }
            }
        }

        bool possible=1;

        for(int i=0; i<n; i++){
            int x = Find(i);
            if(vis[x])continue;
            vis[x]=1;

            data tmp = parent[x];
            ///left down
            if(!(tmp.leftmost>0 || tmp.downmost>0))possible=0;
            ///up right
            if(!(tmp.upmost<Y || tmp.rightmost<X))possible=0;
            ///left right
            if(!(tmp.leftmost>0 || tmp.rightmost<X))possible=0;
            ///up down
            if(!(tmp.upmost<Y || tmp.downmost>0))possible=0;
        }

        if(possible){
                low=mid;
                ans=max(ans,mid);
        }
        else high=mid;
    }

    printf("%0.8lf\n",ans);

return 0;
}
