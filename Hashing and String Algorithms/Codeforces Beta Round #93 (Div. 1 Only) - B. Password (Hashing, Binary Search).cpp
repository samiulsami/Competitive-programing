#include<bits/stdc++.h>
using namespace std;
/*
    Problem  Codeforces Beta Round #93 (Div. 1 Only) - B. Password
    Verdict AC
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int rand(int l, int r){uniform_int_distribution<int> rangeRNG(l,r); return rangeRNG(rng);}

const int mod1 = 1000005541;
const int mod2 = 1000011823;
const int b1 = rand(149,1<<10), b2 = rand(137,1<<9);

vector<pair<int,int> >P{{1,1}};

struct Hash{
    vector<pair<int,int> >H;
    int n;
    Hash(const char *s, int n):n(n), H(n+2){
        while((int)P.size()<=n+1)
            P.push_back({(1LL*P.back().first*b1)%mod1, (1LL*P.back().second*b2)%mod2});

        for(int i=0; i<n; i++){
            H[i+1].first = (1LL*H[i].first + (1LL*(s[i]-'a'+1)*P[i].first))%mod1;
            H[i+1].second = (1LL*H[i].second + (1LL*(s[i]-'a'+1)*P[i].second))%mod2;
        }
    }

    pair<int,int> getHash(int l, int r){
        int h1 = (H[r].first-H[l-1].first+mod1)%mod1;
        h1 = (1LL*h1*P[n-r].first)%mod1;
        int h2 = (H[r].second-H[l-1].second+mod2)%mod2;
        h2 = (1LL*h2*P[n-r].second)%mod2;
        return {h1,h2};
    }
};

char st[int(1e6+5)];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    scanf("%s",&st);
    int n = strlen(st);
    Hash strHash(st,n);

    vector<pair<pair<int,int>,int> >hashLen;
    for(int i=1; i<n; i++){
        if(strHash.getHash(1,i)==strHash.getHash(n-i+1,n)){
            hashLen.push_back({strHash.getHash(1,i),i});
        }
    }

    int ans=0,low=0,high = (int)hashLen.size()-1,mid;

    while(low<=high){
        mid=(low+high)/2;
        int len = hashLen[mid].second;
        bool pos=0;

        for(int i=2; i<n-len+1; i++){
            if(strHash.getHash(i,i+len-1)==hashLen[mid].first){
                pos=1;
                break;
            }
        }
        if(pos){
            ans=max(ans,len);
            low=mid+1;
        }
        else high=mid-1;
    }

    if(ans>0)for(int i=0; i<ans; i++)printf("%c",st[i]);
    else printf("Just a legend\n");

return 0;
}
